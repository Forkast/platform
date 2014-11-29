#include <QtWidgets>
#include "window.h"

int main(int argc, char * argv[])
{
	//TODO CFiend QApplication -> QCoreApplication
	QApplication app(argc, argv);
	app.setApplicationName("Platform v.01");
	MainWindow mainWin(nullptr, 0);
	mainWin.show();
	return app.exec();
}
