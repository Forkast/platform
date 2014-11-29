#include "server.h"
#include <QDebug>

HttpServer::HttpServer(QObject * parent)
	:	server(parent)
{
	connect(&server, &QTcpServer::newConnection, this, &HttpServer::makeConnection);
	connect(this, &HttpServer::closeSignal, this, &HttpServer::closeConnection);
}

void HttpServer::makeConnection()
{
	Socket * socket = new Socket(nextPendingConnection());
	sockets.append(socket);
	connect(socket, &Socket::readyRead, this, &HttpServer::readData);
}

void HttpServer::sendHead(Socket * socket, int size)
{
	QString buffer = "HTTP/1.1 200 OK\r\nServer: Platforma v.01\r\nContent-Length: 623\r\nContent-Type: text/html\r\n\r\n"; //TODO: QString::arg()
	emit debug(buffer);

	socket->write(buffer.toLocal8Bit());

	emit debug("My answer:\n");
	emit debug(buffer);
	emit debug("Header has been send\n");
}

//TODO: Well.. hashysh. files.

void HttpServer::readData(Socket * socket)
{
	const int BUFFER = 256; //TODO CFiend wszystko co buforujesz niech ma rozmiar n * 4 KiB
	qint64 n;
	char cmd[16], path[64], vers[16], buffer[BUFFER];
	QFile * data = new QFile("../data/index.html");
	data->open(QIODevice::ReadOnly);
	QString file = data->readAll();

	emit debug("Clients request:");
	n = socket->readLine(buffer, BUFFER);
	sscanf(buffer, "%s %s %s", cmd, path, vers); //TODO CFiend QRegularExpression
	emit debug(buffer);
	while ((n = socket->readLine(buffer, BUFFER)) > 0) {
		if (n == 2 && buffer[0] == '\r' && buffer[1] == '\n')
			break;
		emit debug(buffer);
		emit debug ("\n");
	}
	emit debug("Check if client is reliable");
	if (strcmp(cmd, "GET") || (strcmp(vers, "HTTP/1.0") && strcmp(vers, "HTTP/1.1"))) {
		emit debug("\t\t\t\t\t[FAILED]\n");
	} else {
		emit debug("\t\t\t\t\t[OK]\n\n");
		sendHead(socket, file.size());
		sendData(socket, path);
		socket->write(file.toLocal8Bit());
		emit debug("\t\t\t\t\t[OK]\n\n");
	}
}

void HttpServer::sendData(Socket * socket, const QString &path)
{
	emit debug("Sending index.html");
}

void HttpServer::closeConnection(Socket * socket)
{
	socket->close();
}

QTcpSocket* HttpServer::nextPendingConnection()
{
	return server.nextPendingConnection();
}

bool HttpServer::isListening()
{
	return server.isListening();
}

bool HttpServer::listen(const QHostAddress & address = QHostAddress::Any, quint16 port = 0)
{
	return server.listen(address, port);
}

void HttpServer::close()
{
	server.close();
}