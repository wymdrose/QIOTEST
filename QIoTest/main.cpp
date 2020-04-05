#include "qiotest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QIoTest w;
	w.show();
	return a.exec();
}
