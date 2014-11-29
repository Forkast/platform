#include "socket.h"

Socket::Socket(QTcpSocket * socket)
	:	socket(socket)
{
	connect(socket, &QTcpSocket::readyRead, [this](){
		emit readyRead(this);
	});
}
void Socket::close()
{
	socket->close();
}
qint64 Socket::write(const QByteArray &mssg)
{
	return socket->write(mssg);
}
qint64 Socket::readLine(char * data, qint64 maxSize)
{
	return socket->readLine(data, maxSize);
}
QByteArray Socket::readLine(qint64 maxSize = 0)
{
	return socket->readLine(maxSize);
}