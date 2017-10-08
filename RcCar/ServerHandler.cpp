#include "ServerHandler.h"

ServerHandler::ServerHandler(QObject *parent)
{
}

void ServerHandler::serverSetup()
{
	server = new VideoServer(this);
	
	if (!server->listen()) {
		qDebug() << "Unable to start the server: " << server->errorString();
	}
	
	QString ipAddress;
	QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
	//first non local IPv4 Address
	int ipAddressListlength = ipAddressList.length();
	for (int i = 0; i < ipAddressListlength; ++i)
	{
		if (ipAddressList.at(i) != QHostAddress::LocalHost && ipAddressList.at(i).toIPv4Address())
		{
			ipAddress = ipAddressList.at(i).toString();
			break;
		}
	}
	
	//if we did not find one, use IPv4 localhost
	if (ipAddress.isEmpty())
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
	
	qDebug() << "Server is listening on IP: " << ipAddress << "\nPort: " << server->serverPort();
}
	
ServerHandler::~ServerHandler()
{
}
