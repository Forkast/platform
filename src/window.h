#pragma once

#include <QtWidgets>
#include <QtNetwork>
#include "server.h"

class MainWindow : public QMainWindow
{

	Q_OBJECT;

public:

	MainWindow(QWidget * parent, Qt::WindowFlags flags);

private:
	HttpServer server;
	QTextEdit debugWin;
public slots:
	void newServer();
	void closeServer();
	void closeWindow();
	void debug(QString);
};