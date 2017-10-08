#include "VideoServer.h"
#include "ServerThread.h"

VideoServer::VideoServer(QObject *parent)
{
}

VideoServer::~VideoServer()
{
}

void VideoServer::incomingConnection(qintptr socketDescriptor)
{
	QThread *thread = new QThread(this);
	ServerThread *serverThread = new ServerThread(socketDescriptor);
	serverThread->moveToThread(thread);
	connect(thread, &QThread::started, serverThread, &ServerThread::run);
	connect(thread, &QThread::finished, thread, &QObject::deleteLater);
	//connect(serverThread, &ServerThread::error, this,);
	thread->start();
}

