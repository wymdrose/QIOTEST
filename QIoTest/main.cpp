#include "qiotest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
//	qInstallMessageHandler(Dologs::outputMessage);

	QIoTest* w = new QIoTest();
	w->show();
	
	gpDoSqlite = std::make_shared<DatabaseCover::MySqLite>("dosqlite");
	Dologs::outlog("begin......");
	gpDoSqlite->open();

	return a.exec();
}
