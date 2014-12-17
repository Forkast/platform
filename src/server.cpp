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
	connect(socket, &Socket::readyRead, this, &HttpServer::readAllYouCan);
	connect(this, &HttpServer::allRead, this, &HttpServer::understandData);
}
//TODO: Well.. hashysh. files.

void HttpServer::readAllYouCan(Socket *socket)
{
	socket->readAll();

	//TODO: if bad data

	if (socket->endOfRequest()) {
		emit allRead(socket);
		emit debug("Emitted\n");
	}
}

void HttpServer::sendData(Socket * socket, const QString &cmd, const QString &path)
{
	emit debug("Requested file: ../data" + path + "\n");
	QFile data;
	if (path != "/")
		data.setFileName("../data" + path);
	else
		data.setFileName("../data/index.html");
	if (!(data.open(QIODevice::ReadOnly))) {
		emit debug("Failed to open requested file\n");
		sendHead(socket, 0, 400);
		//TODO: bad request
	} else {
		QString buffer = data.readAll();
		emit debug(buffer + "\n");
		sendHead(socket, buffer.toLocal8Bit().size(), 200);
		socket->write(buffer.toLocal8Bit());
	}
}

void HttpServer::sendHead(Socket * socket, int size, int statusNo)
{
	QString status;
	if (statusNo / 100 == 2)
		status = "OK";
	else
		status = "ERROR";
	QString buffer = QString("HTTP/1.1 %1 " + status +"\r\nServer: Platforma v.01\r\nContent-Length: %2\r\nContent-Type: text/html\r\n\r\n").arg(statusNo).arg(size);
	socket->write(buffer.toLocal8Bit());

	emit debug("My answer:\n");
	emit debug(buffer);
	emit debug("Header has been send\n");
}

void HttpServer::understandData(Socket * socket)
{
//TODO CFiend wszystko co buforujesz niech ma rozmiar n * 4 KiB
	QString cmd, path, vers, crlf;
	emit debug("Started parsering\n");

	QRegularExpression head("^(?<command>GET|POST) (?<path>\\S+) (?<vrs>HTTP/\\d\\.\\d)(?<crlf>\\r\\n)");

	emit debug("Clients request:");

	QRegularExpressionMatch match = head.match(socket->getRequest());
	if (match.hasMatch()) {
		emit debug("Match found\n");
		cmd = match.captured("command");
		path = match.captured("path");
		vers = match.captured("vrs");
		crlf = match.captured("crlf");
		emit debug(cmd + " " + path + " " + vers + crlf);
		sendData(socket, cmd, path);
	} else {
		emit debug("Match not found\n");
	}
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
/*
void HttpServer::parser()
{
	
}*/
