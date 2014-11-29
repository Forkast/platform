#include "window.h"

MainWindow::MainWindow(QWidget * parent = nullptr, Qt::WindowFlags flags = 0)
	: QMainWindow(parent, flags), server(parent)
{
	QMenu * fileMenu = menuBar()->addMenu("&File");

	QWidget * centralWidget = new QWidget(this);
	QHBoxLayout * mainLay = new QHBoxLayout(centralWidget);

	for (auto x : std::initializer_list <std::tuple <QAction **, const QString &, const QKeySequence &, std::function <void()> > > {
			{&startAction, "&Start", Qt::CTRL + Qt::Key_N, &MainWindow::newServer},
			{&stopAction, "S&top", Qt::CTRL + Qt::Key_C, &MainWindow::closeServer},
			{&quitAction, "&Quit", Qt::CTRL + Qt::Key_Q, &MainWindow::closeWindow},
		}) {
			QAction **a = std::get<0>(x);
			*a = new QAction(std::get<1>(x), this);
			connect(*a, &QAction::triggered, this, std::get<3>(x));
			*a->setShortcut(std::get<2>(x));
		}

// 	QAction * startAction = new QAction("&Start", this);
// 	connect(startAction, &QAction::triggered, this, &MainWindow::newServer);
// 	startAction->setShortcut(Qt::CTRL + Qt::Key_N);

// 	QAction * stopAction = new QAction("S&top", this);
// 	connect(stopAction, &QAction::triggered, this, &MainWindow::closeServer);
// 	stopAction->setShortcut(Qt::CTRL + Qt::Key_C);

// 	QAction * quitAction = new QAction("&Quit", this);
// 	connect(quitAction, &QAction::triggered, this, &MainWindow::closeWindow);
// 	quitAction->setShortcut(Qt::CTRL + Qt::Key_Q);

	connect(&server, &HttpServer::debug, this, &MainWindow::debug);

	for (QAction * action : {startAction, stopAction, quitAction})
		fileMenu->addAction(action);

	debugWin.setReadOnly(true);
	QColor green(50, 200, 50);
	QColor black(0, 0, 0);
	debugWin.setTextBackgroundColor(black);
	debugWin.setTextColor(green);

	debugWin.setText("Server HTTP ver.0.01\n\n");

	mainLay->addWidget(debugWin);
	centralWidget->setLayout(mainLay);
	setCentralWidget(centralWidget);
}

void MainWindow::newServer()
{
	if (!server.isListening()) {
		emit debug("Starting Server on port 3560");
		if (!server.listen(QHostAddress::Any, 3560))
			emit debug("\t\t\t\t[FAILED]\n");
		else
			emit debug("\t\t\t\t[OK]\n");
	}
}

void MainWindow::closeServer()
{
	if (server.isListening()) {
		emit debug("Closing Server");
		server.close();
		emit debug("\t\t\t\t\t[OK]\n");
	}
}
void MainWindow::closeWindow()
{
	server.close();
	close();
}
void MainWindow::debug(QString string)
{
	debugWin.setText(debugWin.toPlainText() + string);
}
