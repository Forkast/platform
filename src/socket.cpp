#include "socket.h"

Socket::Socket(QTcpSocket * socket)
	:	socket(socket)
{
	connect(socket, &QTcpSocket::readyRead, [this]{
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