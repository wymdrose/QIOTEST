#include "qiotest.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
//	qInstallMessageHandler(Dologs::outputMessage);


	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));


	QIoTest* w = new QIoTest();
	w->show();

	gpDoSqlite = std::make_shared<DatabaseCover::MySqLite>("dosqlite");
	Dologs::outlog("begin......");
	gpDoSqlite->open();

	return a.exec();
}
