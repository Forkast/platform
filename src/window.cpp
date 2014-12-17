#include "window.h"

MainWindow::MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = 0)
	: QMainWindow(parent, flags), server(parent)
{
	QMenu *fileMenu = menuBar()->addMenu("&File");

	QWidget *centralWidget = new QWidget(this);
	QHBoxLayout *mainLay = new QHBoxLayout(centralWidget);

	QAction *startAction = nullptr, *stopAction = nullptr, *quitAction = nullptr;

	struct ActionDescriptor
	{
		QAction **act;
		const QString str;
		const QKeySequence key;
		void (MainWindow::*fun)();
	};

	for (const auto &x : std::initializer_list <ActionDescriptor> {
			{&startAction, QString("&Start"), QKeySequence(Qt::CTRL + Qt::Key_N), &MainWindow::newServer},
			{&stopAction, QString("S&top"), QKeySequence(Qt::CTRL + Qt::Key_C), &MainWindow::closeServer},
			{&quitAction, QString("&Quit"), QKeySequence(Qt::CTRL + Qt::Key_Q), &MainWindow::closeWindow},
		}) {
			QAction **a = x.act;
			*a = new QAction(x.str, this);
			connect(*a, &QAction::triggered, this, x.fun);
			(*a)->setShortcut(x.key);
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
