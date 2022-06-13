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

bool lineTest(itemTest item);

public slots:
	void slotStartList();
	void slotFindBegin();
	void slotFind(QString);

	void readReady();
	void slotValuesReady();
	void slotCheckModbus();
	void slotReadAll();
	void slotReadRequset(int);

signals:
	void signalStartList();
	void signalFindBegin();
	void signalFind(QString);

	void signalCheckModbus();
	void signalReadAll();
	void signalValuesReady();
	void signalReadRequset(int);

private:
	Ui::QIoTestClass ui;
	
	QLabel *mFindPointLabel;
	QString mFilePath;
	
	void pushButtonConnectSlot();
	void pushButtonReadSlot();
	void modbudConnectSources();
	void updateSets(QVector<QSet<int>>& sets, int L, int R);
	void updateModbusSets();
	void updateTestTask();
	bool checkShort(QSet<int> item, int L, int R);
	bool checkPins(itemTest item);
	bool selfCheck();


	QMap<QString, QList<QString>> mapTest;	//need to test from cateory
	std::vector<int> mCurBoards;
	QList<itemTest> mListTest;	//read all items from local file.
	QSet<QString> mCurCategorys;
	bool mbPause = false;
	bool mbExit = false;
	//---------------------------------------------------------------------//

	QVector<QSet<int>> modbusSets;
	QVector<QSet<int>> testTaskSets;	//from csv
	QVector<qint16> mValuse;	//read all from modbus
	int curReadIndex = 0;
};

#endif // QIOTEST_H
