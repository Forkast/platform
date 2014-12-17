#pragma once

#include <QtNetwork>

class Socket : public QObject
{

	Q_OBJECT;

public:
	Socket(QTcpSocket *socket);
	void close();
	qint64 write(const QByteArray &mssg);
	qint64 readLine(char *data, qint64 maxSize);
	QByteArray readLine(qint64 maxSize);
	void append(const QByteArray &data);
	void readAll();
	bool endOfRequest();
	QString getRequest();
signals:
	void readyRead(Socket *socket);
private:
	QTcpSocket *socket;
	QString buffer;
};