#ifndef QIOTEST_H
#define QIOTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_qiotest.h"
#include "global.h"
#include <QList>

enum H_L
{
	L, H
};

struct itemTest
{
	bool bInlist;
	int result;
	int rowNo;
	QString coordinateL;
	QString coordinateR;
	QString category;
	QString pinL;
	QString pinR;

};

class QIoTest : public QMainWindow
{
	Q_OBJECT

public:
	QIoTest(QWidget *parent = 0);
	~QIoTest();

bool inline _checkPins(itemTest item);
bool inline lineTest(itemTest item);

public slots:
	void slotStartList();
	void slotFindBegin();
	void slotFind(QString);
signals:
	void signalStartList();
	void signalFindBegin();
	void signalFind(QString);
private:
	Ui::QIoTestClass ui;
	
	QLabel *mFindPointLabel;
	QString mFilePath;
};

#endif // QIOTEST_H
