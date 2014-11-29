#pragma once

#include <QtWidgets>
#include <QtNetwork>
#include "socket.h"

class HttpServer : public QObject
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
	void close();
	bool isListening();
	bool listen(const QHostAddress & address, quint16 port);
	QTcpSocket* nextPendingConnection();
	void makeConnection();
	void closeConnection(Socket * socket);
	void sendHead(Socket * socket, int size);
	void sendData(Socket * socket, const QString &path);
	void readData(Socket * socket);
};
