#include "ServerHandler.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
	ServerHandler serverHandler;
	
	serverHandler.serverSetup();
	
    return a.exec();
}
