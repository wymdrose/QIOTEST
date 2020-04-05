#include "qiotest.h"
#include <ActiveQt/QAxWidget>
#include <QModelIndex>
#include <QModelIndexList>
#include <QItemSelectionModel>
#include <vector>
#include <QVBoxLayout>

GLOBAL

using namespace std;
using namespace Drose;

QMap<QString, QList<QString>> mapTest;
vector<int> mCurBoards;

void inline _initBoard(int boardNo)
{
	QByteArray send;
	QByteArray tRecv;
	send.resize(12);
	send[0] = 0x7E;
	send[1] = 0x00;
	send[2] = 0xFF;
	send[3] = 0xFF;
	send[4] = 0xFF;
	send[5] = 0xFF;
	send[6] = 0xFF;
	send[7] = 0xFF;
	send[8] = 0xFF;
	send[9] = 0xFF;
	send[10] = 0x00;
	send[11] = 0x7E;

	gpTcpClientVector[boardNo]->communicate(send, tRecv);
}

bool inline _findPin(int boardNo, int& pin)
{
	pin = 63;
	return true;

	//
	QByteArray send;
	QByteArray tRecv;
	send.resize(12);
	send[0] = 0x7E;
	send[1] = 0x02;
	send[2] = 0x00;
	send[3] = 0x00;
	send[4] = 0x00;
	send[5] = 0x00;
	send[6] = 0x00;
	send[7] = 0x00;
	send[8] = 0x00;
	send[9] = 0x00;
	send[10] = 0x00;
	send[11] = 0x7E;

	gpTcpClientVector[boardNo]->communicate(send, tRecv);

	for (size_t i = 0; i < 8; i++)
	{
		byte tByte = tRecv.at(i + 2);

		if (tByte == 0xFF)
		{
			continue;
		}

		for (size_t j = 0; j < 8; j++)
		{
			if (!(tByte & (1 << j)))
			{
				pin = 8 * i + j;
				return true;
			}
		}
	}

	return false;
}

void inline _outPin(int boardNo, int pinNo = 0, H_L v = L)
{
	QByteArray send;
	QByteArray tRecv;
	send.resize(12);

	send[0] = 0x7E;
	send[1] = 0x00;
	send[2] = 0xFF;
	send[3] = 0xFF;
	send[4] = 0xFF;
	send[5] = 0xFF;
	send[6] = 0xFF;
	send[7] = 0xFF;
	send[8] = 0xFF;
	send[9] = 0xFF;
	send[10] = 0x00;
	send[11] = 0x7E;

	send[pinNo / 8 + 2] = ~(H << (pinNo % 8));
	gpTcpClientVector[boardNo]->communicate(send, tRecv);

	//write
	send[1] = 0x01;
	gpTcpClientVector[boardNo]->communicate(send, tRecv);

}

bool inline _checkPins(itemTest item)
{
	QByteArray send;
	QByteArray tRecv;
	send.resize(12);
	tRecv.resize(12);

	send[0] = 0x7E;
	send[1] = 0x02;
	send[2] = 0x00;
	send[3] = 0x00;
	send[4] = 0x00;
	send[5] = 0x00;
	send[6] = 0x00;
	send[7] = 0x00;
	send[8] = 0x00;
	send[9] = 0x00;
	send[10] = 0x00;
	send[11] = 0x7E;

	QVector<int> vRight;


	for (auto it = mCurBoards.begin(); it != mCurBoards.end(); ++it)
	{
		int index = *it;

		if (index > gpTcpClientVector.size()-1)
		{
			qDebug() << QString("no board %0").arg(index) << "\r";
			Sleep(10);
			continue;
		}

		gpTcpClientVector[index]->communicate(send, tRecv);
		
		for (size_t i = 0; i < 8; i++)
		{
			byte tByte = tRecv.at(i + 2);

			if (tByte == 0xFF)
			{
				continue;
			}

			for (size_t j = 0; j < 8; j++)
			{
				if (!(tByte & (1 << j)))
				{
					vRight.append(64 * i + j);
				}
			}
		}
	}

	if (vRight.isEmpty())
	{
		return false;
	}

	if (!vRight.contains(item.pinR.toInt()))
	{
		return false;
	}

	//

	for (auto it = vRight.begin(); it != vRight.end(); ++it)
	{
		if (!mapTest[item.pinL].contains(QString(*it)))
		{
			return false;
		}
	}
	
	return true;

}

void inline lineTest(itemTest item)
{
	int boardNo = (item.pinL.toInt() - 1) / 64;
	int pinNo = (item.pinL.toInt() - 1) % 64;

	if (boardNo > gpTcpClientVector.size() - 1)
	{
		qDebug() << QString("no board %0").arg(boardNo) << "\r";
		Sleep(10);
		return;
	}

	_outPin(boardNo, pinNo);

	_checkPins(item);
}

QIoTest::QIoTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	
	gpUi = &ui;
	
	gpSignal = std::make_shared<Drose::MySignalUi>();

	gExePath = QCoreApplication::applicationDirPath();
	auto a = gExePath;

	auto ptCsv = std::shared_ptr<FileIo::CsvFile>(new FileIo::CsvFile(gExePath + "/cfg/ipVector.csv"));

	ptCsv->get(ipVector);

	for (size_t i = 0; i < ipVector.size(); i++)
	{
		qDebug() << QString(ipVector[i][0]) << " : " << QString(ipVector[i][1]);

		gpTcpClientVector.push_back(new CommunicateClass::TcpClient(ipVector[i][0], 5001));
		
		if (!gpTcpClientVector[i]->init())
		{
			gpSignal->showDialogSignal("", ipVector[i][0] + ": connect error");
		}

		_initBoard(i);
	}

	connect(ui.pushButtonMoveUp, &QPushButton::clicked, [this]()
	{
		QModelIndexList indexes = ui.listWidgetDown->selectionModel()->selectedRows();

		if (indexes.size() > 0) 
		{
			auto tItem = ui.listWidgetDown->takeItem(indexes.at(0).row());
			ui.listWidgetUp->addItem(tItem);
			mCurCategorys.insert(tItem->text());
		}
	});

	connect(ui.pushButtonMoveDown, &QPushButton::clicked, [this]() {
		QModelIndexList indexes = ui.listWidgetUp->selectionModel()->selectedRows();

		if (indexes.size() > 0) 
		{
			auto tItem = ui.listWidgetUp->takeItem(indexes.at(0).row());
			ui.listWidgetDown->addItem(tItem);
			mCurCategorys.remove(tItem->text());
		}

	});
	
	connect(ui.pushButtonOpenFile, &QPushButton::clicked, [this]() {
		
		FileIo::xlsxFile file;
		file.readExcel(gExePath + "/LCA15150A16541588.xlsx", ui.tableWidget);
		
		
		
		auto count = ui.tableWidget->rowCount();

		mListTest.clear();
		for (size_t i = 0; i < ui.tableWidget->rowCount(); i++)
		{
			itemTest tItem;
			tItem.bInlist = true;
			tItem.result = -1;
			tItem.rowNo = i;
			tItem.coordinateL = ui.tableWidget->item(i, 1)->text();
			tItem.coordinateR = ui.tableWidget->item(i, 2)->text();
			tItem.category = ui.tableWidget->item(i, 3)->text();
			tItem.pinL = ui.tableWidget->item(i, 8)->text();
			tItem.pinR = ui.tableWidget->item(i, 9)->text();
			mListTest.push_back(tItem);

			mCurCategorys.insert(ui.tableWidget->item(i, 3)->text());
		}

		for (auto it = mCurCategorys.begin(); it != mCurCategorys.end(); ++it)
		{
			ui.listWidgetUp->addItem(*it);			
		}
				
		Sleep(0);
	});

	connect(ui.pushButtonSave, &QPushButton::clicked, [this]() {

		FileIo::xlsxFile file;
		file.writeExcel(gExePath + "/MCA-III20180802.xlsx", ui.tableWidget);

	});
	
	// 
	connect(ui.pushButtonFindpoint, &QPushButton::clicked, [this]() {
		QDialog* tpDialog = new QDialog();
		mFindPointLabel = new  QLabel("pin:    ");
		QVBoxLayout *tpLayout = new (QVBoxLayout);
		
		tpLayout->addWidget(mFindPointLabel);
		tpDialog->setLayout(tpLayout);

		signalFindBegin();
		tpDialog->exec();
	});


	connect(this, SIGNAL(signalFind(QString)), this, SLOT(slotFind(QString)), Qt::QueuedConnection);

	connect(this, SIGNAL(signalFindBegin()), this, SLOT(slotFindBegin()), Qt::QueuedConnection);

	connect(ui.pushButtonStart, &QPushButton::clicked, [this]() {

		/*
		QByteArray send;
		QByteArray tRecv;
		send.resize(12);

		send[0] = 0x7E;
		send[1] = 0x00;
		send[2] = 0x00;
		send[3] = 0x00;
		send[4] = 0x00;
		send[5] = 0x00;
		send[6] = 0x00;
		send[7] = 0x00;
		send[8] = 0x00;
		send[9] = 0x00;
		send[10] = 0x00;
		send[11] = 0x7E;

		gpTcpClientVector[2]->communicate(send, tRecv);

		//
		send[0] = 0x7E;
		send[1] = 0x00;
		send[2] = 0xFF;
		send[3] = 0xFF;
		send[4] = 0xFF;
		send[5] = 0xFF;
		send[6] = 0xFF;
		send[7] = 0xFF;
		send[8] = 0xFF;
		send[9] = 0xFF;
		send[10] = 0x00;
		send[11] = 0x7E;

		gpTcpClientVector[3]->communicate(send, tRecv);
	

		//
		send[0] = 0x7E;
		send[1] = 0x01;
		send[2] = 0x00;
		send[3] = 0x00;
		send[4] = 0x00;
		send[5] = 0x00;
		send[6] = 0x00;
		send[7] = 0x00;
		send[8] = 0x00;
		send[9] = 0x00;
		send[10] = 0x00;
		send[11] = 0x7E;

		gpTcpClientVector[2]->communicate(send, tRecv);


		//
		send[0] = 0x7E;
		send[1] = 0x02;
		send[2] = 0x00;
		send[3] = 0x00;
		send[4] = 0x00;
		send[5] = 0x00;
		send[6] = 0x00;
		send[7] = 0x00;
		send[8] = 0x00;
		send[9] = 0x00;
		send[10] = 0x00;
		send[11] = 0x7E;

		gpTcpClientVector[3]->communicate(send, tRecv);
		*/
		
		for (auto it = mListTest.begin(); it != mListTest.end(); ++it)
		{			
			if (!mCurCategorys.contains(it->category))
			{
				it->bInlist = false;
				continue;
			}

			mapTest[it->pinL].append(it->pinR);

			//
			mCurBoards.push_back(it->pinL.toInt() / 64);
			mCurBoards.push_back(it->pinR.toInt() / 64);
			
			sort(mCurBoards.begin(), mCurBoards.end());
			mCurBoards.erase(unique(mCurBoards.begin(), mCurBoards.end()), mCurBoards.end());
		}
		
		signalStartList();

	});
	
	connect(this, SIGNAL(signalStartList()), this, SLOT(slotStartList()));

}

QIoTest::~QIoTest()
{

}

void QIoTest::slotFind(QString pin)
{
	mFindPointLabel->setText("Find pin: " + pin);
}

void QIoTest::slotFindBegin()
{
	for (size_t i = 0; i < gpTcpClientVector.size(); i++)
	{
		_initBoard(i);
	}
	
	while (true)
	{
		int tPin;
		for (size_t i = 0; i < gpTcpClientVector.size(); i++)
		{
			if (_findPin(i, tPin))
			{
				signalFind(QString("%0").arg(tPin * i));
			}
		}

		QApplication::processEvents();
	}
}

void QIoTest::slotStartList()
{
	for (auto it = mListTest.begin(); it != mListTest.end(); ++it)
	{
		if (!mCurCategorys.contains(it->category))
		{
			it->bInlist = false;
			continue;
		}

		lineTest(*it);

		QApplication::processEvents();
	}
}
