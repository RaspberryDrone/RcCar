#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QProcess>
#include <QStringList>
#include <QString>
#include <QByteArray>
#include <QDataStream>
#include <QVector>
#include <QHostAddress>

class ServerThread : public QObject
{
	Q_OBJECT
public:
	ServerThread(int socketDescriptor, QObject *parent = 0);
	
	void run();
	~ServerThread();
	
signals:
	void error(QTcpSocket::SocketError socketError);
	
private slots :
	void sendDataToClient();
	void readTcpData();
	
private:	
	int socketDescriptor;
	int videoSocketPort;
	
	QStringList arguments;
	
	int hight = 720;
	int width = 1280;
	int fps = 48;
	int bitrate = 3000000;
	int port;
	
	bool setupDone = false;
	
	QHostAddress hostAddress;
	
	QProcess *cameraProcess;
	QTcpSocket *tcpSocket;
	QUdpSocket *udpSocket;
	
	void setupProcess();
	void initalSetup();
};


#endif