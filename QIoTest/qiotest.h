#ifndef QIOTEST_H
#define QIOTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_qiotest.h"
#include "global.h"
#include <QList>
#include <set>
#include <QTimer>
#include <QEventLoop>

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

	void slotValuesReady();

signals:
	void signalStartList();
	void signalFindBegin();
	void signalFind(QString);

	void signalValuesReady();


private:
	void _sleeploop(int ms){
		QEventLoop loop;
		QTimer::singleShot(ms, &loop, SLOT(quit()));
		loop.exec();
	}

	bool msgParse(bool bfirst = false);

private:
	Ui::QIoTestClass ui;
	
	QLabel *mFindPointLabel;
	QString mFilePath;
	QString inputFile_;
	
	void pushButtonConnectSlot();
	void pushButtonReadSlot();
	void modbudConnectSources();
	void comConnectSources();
	void updateSets(QVector<QSet<int>>& sets, int L, int R);
	void updateModbusSets();
	void updateTestTask();
	bool checkShort(QSet<int> item, int L, int R);
	bool checkPins(itemTest item);
	bool selfCheck();


	QMap<QString, QList<QString>> mapTest;	//need to test from cateory
	std::vector<int> mCurBoards;
	QList<itemTest> mListTest;	//read all items from local file.
	QList<itemTest> ng_list_;
	QSet<QString> mCurCategorys;
	bool mbPause = false;
	bool mbExit = false;
	bool bStep_ = false;
	bool enShort_ = false;
	//---------------------------------------------------------------------//

	QVector<QSet<int>> modbusSets;
	QVector<QSet<int>> testTaskSets;	//from csv
	std::set<std::set<uint16_t>> com_pairs_;
	bool parse_done_;

	bool findRequest = true;
	int findIndex = 0;

	QSettings settings{ "app.ini", QSettings::IniFormat };
	QString lineMsg_;
};

#endif // QIOTEST_H
