#pragma once

#include <QtNetwork>

class Socket : public QObject
{

	Q_OBJECT;

private:
	QTcpSocket * socket;
public:
	Socket(QTcpSocket * socket);
	void close();
	qint64 write(const QByteArray &mssg);
	QByteArray readLine(qint64 maxSize);
	qint64 readLine(char * data, qint64 maxSize);
signals:
	void readyRead(Socket * socket);
};