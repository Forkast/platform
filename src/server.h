#pragma once

#include <QtWidgets>
#include <QtNetwork>
#include "socket.h"

class HttpServer
{

	Q_OBJECT;

public:
	HttpServer(QObject * parent);
private:
	QTcpServer server;
	QVector <Socket *> sockets;
signals:
	void debug(const QString &msg);
	void closeSignal(Socket * socket);
public:
	void makeConnection();
	void closeConnection(Socket * socket);
	void sendHead(Socket * socket, int size);
	void sendData(Socket * socket, const QString &path);
	void readData(Socket * socket);
};
