#pragma once

#include <QtWidgets>
#include <QtNetwork>
#include "socket.h"

class HttpServer : public QObject
{

	Q_OBJECT;

public:
	HttpServer(QObject *parent);
	void makeConnection();
	void readAllYouCan(Socket *socket);
	void sendData(Socket * socket, const QString &cmd, const QString &path);
	void sendHead(Socket * socket, int size, int statusNo);
	void understandData(Socket * socket);
	void closeConnection(Socket *socket);
	QTcpSocket* nextPendingConnection();
	bool isListening();
	bool listen(const QHostAddress &address, quint16 port);
	void close();
signals:
	void debug(const QString &msg);
	void closeSignal(Socket *socket);
	void allRead(Socket *socket);
private:
	QTcpServer server;
	QVector <Socket *> sockets;
};
