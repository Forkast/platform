#pragma once

#include <QtNetwork>

class Socket : public QObject
{

	Q_OBJECT;

private:
	QTcpSocket * socket;
	Socket(QTcpSocket * socket);
public:
	void close();
	qint64 write(const QByteArray &mssg);
signals:
	void readyRead(Socket * socket);
};