#include "window.h"

MainWindow::MainWindow(QWidget * parent = nullptr, Qt::WindowFlags flags = 0)
	: QMainWindow(parent, flags), server(parent)
{
	QMenu * fileMenu = menuBar()->addMenu("&File");

	QWidget * centralWidget = new QWidget(this);
	QHBoxLayout * mainLay = new QHBoxLayout(centralWidget);

	QAction * startAction, * stopAction, * quitAction;

	for (auto x : std::initializer_list <std::tuple <QAction **, const QString &, const QKeySequence &, std::function <void()> > > {
			{&startAction, "&Start", Qt::CTRL + Qt::Key_N, &MainWindow::newServer},
			{&stopAction, "S&top", Qt::CTRL + Qt::Key_C, &MainWindow::closeServer},
			{&quitAction, "&Quit", Qt::CTRL + Qt::Key_Q, &MainWindow::closeWindow},
		}) {
			QAction **a = std::get<0>(x);
			*a = new QAction(std::get<1>(x), this);
			connect(*a, &QAction::triggered, this, std::get<3>(x));
			(*a)->setShortcut(std::get<2>(x));
			fileMenu->addAction(*a);
		}

	connect(&server, &HttpServer::debug, this, &MainWindow::debug);

	debugWin.setReadOnly(true);
	QColor green(50, 200, 50);
	QColor black(0, 0, 0);
	debugWin.setTextBackgroundColor(black);
	debugWin.setTextColor(green);

	debugWin.setText("Server HTTP ver.0.01\n\n");

	mainLay->addWidget(&debugWin);
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
