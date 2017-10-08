#include "ServerThread.h"

ServerThread::ServerThread(int socketDescriptor, QObject *parent)
{
	this->socketDescriptor = socketDescriptor;
}


ServerThread::~ServerThread()
{
}

/*
	entry point when thread starts
*/
void ServerThread::run()
{
	//connect tcpsocket
	tcpSocket = new QTcpSocket(this);
	connect(tcpSocket, &QIODevice::readyRead, this, &ServerThread::readTcpData);
	
	if (!tcpSocket->setSocketDescriptor(socketDescriptor))
	{
		emit error(tcpSocket->error());
		return;
	}
}

/*
	read data from Tcp connection
*/
void ServerThread::readTcpData()
{
	//first transmission and setup
	if (!setupDone)
	{
		initalSetup();
		setupDone = true;
	}
	//maybe more controll via Tcp later
	
	
}

/*
	do inital setup
*/
void ServerThread::initalSetup()
{
	//read from bytestream to byte array
	QByteArray readByteArray = tcpSocket->readAll();
	QDataStream stream(&readByteArray, QIODevice::ReadWrite);
	QVector<int> ints;
	stream >> ints;
	
	/* to convert 
	QByteArray line;
	QDataStream stream(&line, QIODevice::WriteOnly);
	stream << y;
	*/
	
	//get port for udp connection from array
	port = ints.at(0);
	//check how long ints is if it is only 1 int use default values else use given values
	if (ints.length() > 1)
	{
		hight = ints.at(1);
		width = ints.at(2);
		fps = ints.at(3);
		bitrate = ints.at(4);
	}
	
	//setup the UdpSocket which is used to transmit video
	udpSocket = new QUdpSocket(this);
	hostAddress = tcpSocket->peerAddress();
	
	setupProcess();
}

/*
	setup camera process
*/
void ServerThread::setupProcess()
{
	//start camera process
	QString program = "/usr/bin/raspivid";
	
	arguments	<< "-t" << "0"							//no timeout
				<< "-w" << QString::number(width)
				<< "-h" << QString::number(hight)
				<< "-fps" << QString::number(fps)
				<< "-b" << QString::number(bitrate)
				<< "-l" << "-o -";						//output to sdtout
	
	cameraProcess = new QProcess(this);
	connect(cameraProcess, &QProcess::readyReadStandardOutput, this, &ServerThread::sendDataToClient);
	cameraProcess->start(program, arguments);

}

/*
	take data from camera and transmit via UDP
*/
void ServerThread::sendDataToClient()
{
	QByteArray bArray = cameraProcess->readAllStandardOutput();
	
	/*	prepend array length to array maybe?
	int bArrayLength = bArray.length();
	QByteArray lengthArray;
	QDataStream stream(&lengthArray, QIODevice::WriteOnly);
	stream << bArrayLength;
	
	bArray.prepend(lengthArray);
	*/
	
	udpSocket->writeDatagram(bArray, hostAddress, port);
}