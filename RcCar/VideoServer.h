#ifndef VIDEOSERVER_H
#define VIDEOSERVER_H

#include <QTcpServer>
#include <QThread>


class VideoServer : public QTcpServer
{
	Q_OBJECT
public:
	VideoServer(QObject *parent = 0);
	~VideoServer();
	
protected:
	void incomingConnection(qintptr socketDescriptor);
	
};

#endif
