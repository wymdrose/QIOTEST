#include "qiotest.h"
#include <ActiveQt/QAxWidget>
#include <QModelIndex>
#include <QModelIndexList>
#include <QItemSelectionModel>
#include <vector>
#include <QVBoxLayout>
#include <QFileDialog>

GLOBAL

using namespace std;
using namespace Drose;

QMap<QString, QList<QString>> mapTest;
vector<int> mCurBoards;
QList<itemTest> mListTest;
QSet<QString> mCurCategorys;
bool mbPause = false;
bool mbExit = false;

void inline _updateCurBoards()
{
	mCurBoards.clear();

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
}

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

bool inline lineTest(itemTest item)
{
	int boardNo = (item.pinL.toInt() - 1) / 64;
	int pinNo = (item.pinL.toInt() - 1) % 64;

	if (boardNo > gpTcpClientVector.size() - 1)
	{
		qDebug() << QString("no board %0").arg(boardNo) << "\r";
		Sleep(10);
		return false;
	}

	_outPin(boardNo, pinNo);

	if (!_checkPins(item))
	{
		return false;
	}

	return true;
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

		_updateCurBoards();
	});

	connect(ui.pushButtonMoveDown, &QPushButton::clicked, [this]() {
		QModelIndexList indexes = ui.listWidgetUp->selectionModel()->selectedRows();

		if (indexes.size() > 0) 
		{
			auto tItem = ui.listWidgetUp->takeItem(indexes.at(0).row());
			ui.listWidgetDown->addItem(tItem);
			mCurCategorys.remove(tItem->text());
		}

		_updateCurBoards();
	});
	
	connect(ui.pushButtonOpenFile, &QPushButton::clicked, [this]() {
		
		mFilePath = QFileDialog::getOpenFileName(NULL, QStringLiteral("µµ°¸"), gExePath + "/cfg/", "*.xlsx");

		if (mFilePath.isEmpty())
			return;		

		FileIo::xlsxFile file;
		file.readExcel(mFilePath, ui.tableWidget);
	
		auto count = ui.tableWidget->rowCount();

		mListTest.clear();
		mCurCategorys.clear();

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
				
		_updateCurBoards();
	});
	
	connect(ui.pushButtonEdit, &QPushButton::clicked, [this]() {

		static bool b = false;
		b = !b;
		ui.pushButtonSave->setEnabled(b);

	});

	ui.pushButtonSave->setEnabled(false);
	connect(ui.pushButtonSave, &QPushButton::clicked, [this]() {

		FileIo::xlsxFile file;
		file.writeExcel(mFilePath, ui.tableWidget);

	});
	
	connect(ui.pushButtonSelfCheck, &QPushButton::clicked, [this]() {

		_updateCurBoards();

		//
		for (size_t i = 0; i < mCurBoards.size(); i++)
		{
			int boardNo = mCurBoards[i];
			if (!gpTcpClientVector[boardNo]->init())
			{
				gpSignal->showDialogSignal("", ipVector[boardNo][0] + ": connect error");

				return;
			}

			_initBoard(boardNo);

			//
			int tPin;
			if (_findPin(boardNo, tPin))
			{
				gpSignal->showDialogSignal("", QString("board: %0   pin: %1  error").arg(boardNo).arg(tPin));

				return;
			}
		}
		

	});

	connect(ui.pushButtonLockScreen, &QPushButton::clicked, [this]() {

		QDialog tDialog;
		QLabel tLabel("Lock");
		QVBoxLayout tpLayout;
		tDialog.setFixedSize(500, 400);
		tLabel.setFixedSize(300, 200);
		tpLayout.addWidget(&tLabel);
		tDialog.setLayout(&tpLayout);
		tDialog.exec();

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

	connect(ui.pushButtonPause, &QPushButton::clicked, [this]() {
		mbPause = !mbPause;
		mbPause ? ui.pushButtonPause->setText(QStringLiteral("¼ÌÐø")) : ui.pushButtonPause->setText(QStringLiteral("ÔÝÍ£"));
	});

	connect(ui.pushButtonExit, &QPushButton::clicked, [this]() {
		mbExit = true;

		for (auto it = mListTest.begin(); it != mListTest.end(); ++it)
		{
			ui.tableWidget->item(it->rowNo, 0)->setText("");
			ui.tableWidget->item(it->rowNo, 0)->setBackgroundColor(QColor(255, 255, 255));
		}
	});

	connect(ui.pushButtonStepTest, &QPushButton::clicked, [this]() {
		
		QList<QTableWidgetItem*>items = ui.tableWidget->selectedItems();
		
		int i = ui.tableWidget->row(items.at(0));

		itemTest tItem;
		tItem.bInlist = true;
		tItem.result = -1;
		tItem.rowNo = i;
		tItem.coordinateL = ui.tableWidget->item(i, 1)->text();
		tItem.coordinateR = ui.tableWidget->item(i, 2)->text();
		tItem.category = ui.tableWidget->item(i, 3)->text();
		tItem.pinL = ui.tableWidget->item(i, 8)->text();
		tItem.pinR = ui.tableWidget->item(i, 9)->text();

		ui.labelCoordinateL->setText(tItem.coordinateL);
		ui.labelCoordinateR->setText(tItem.coordinateR);
		ui.labelPinL->setText(tItem.pinL);
		ui.labelPinR->setText(tItem.pinR);
		ui.labelCategory->setText(tItem.category);

		if (!lineTest(tItem))
		{
			ui.labelResult->setText("NG");
			
			ui.tableWidget->item(tItem.rowNo, 0)->setText("NG");
			ui.tableWidget->item(tItem.rowNo, 0)->setBackgroundColor(QColor(255, 0, 0));
		}
		else
		{
			ui.tableWidget->item(tItem.rowNo, 0)->setText("OK");
			ui.tableWidget->item(tItem.rowNo, 0)->setBackgroundColor(QColor(0, 255, 0));
		}
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
		
		ui.pushButtonStart->setEnabled(false);
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
		QApplication::processEvents();

		if (mbExit)
		{
			mbExit = false;
			break;
		}

		if (mbPause)
		{
			it--;
			continue;
		}

		if (!mCurCategorys.contains(it->category))
		{
			it->bInlist = false;
			continue;
		}

		if (!lineTest(*it))
		{	

			ui.labelResult->setText("NG");
			ui.labelCoordinateL->setText(it->coordinateL);
			ui.labelCoordinateR->setText(it->coordinateR);
			ui.labelPinL->setText(it->pinL);
			ui.labelPinR->setText(it->pinR);
			ui.labelCategory->setText(it->category);

			ui.tableWidget->item(it->rowNo, 0)->setText("NG");
			ui.tableWidget->item(it->rowNo, 0)->setBackgroundColor(QColor(255, 0, 0));

			if (QMessageBox::question(this, "", QStringLiteral("Ìø¹ý£¿")) != QMessageBox::Yes)
			{
				break;
			}
		}
		else
		{
			ui.tableWidget->item(it->rowNo, 0)->setText("OK");
			ui.tableWidget->item(it->rowNo, 0)->setBackgroundColor(QColor(0, 255, 0));
		}
			
	}

	ui.pushButtonStart->setEnabled(true);
}
