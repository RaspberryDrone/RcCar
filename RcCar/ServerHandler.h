#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>

#include "VideoServer.h"

class ServerHandler : public QObject
{
	Q_OBJECT
public:
	ServerHandler(QObject *parent = 0);
	~ServerHandler();
	
	void serverSetup();
	
private:
	VideoServer *server;
};

#endif
