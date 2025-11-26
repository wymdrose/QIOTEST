#include "qiotest.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
//#include <login.hpp>

#include <login.h>
#pragma comment(lib, "login.lib")

int loginMode(0);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
//	qInstallMessageHandler(Dologs::outputMessage);


	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

	Login L(QCoreApplication::applicationDirPath() + "/obc.png", loginMode);
	if (!loginMode){
		return 0;
	}
	

	QIoTest* w = new QIoTest();
	w->showMaximized();
	w->show();

	gpDoSqlite = std::make_shared<DatabaseCover::MySqLite>("dosqlite");
	Dologs::outlog("begin......");
	gpDoSqlite->open();

	return a.exec();
}
