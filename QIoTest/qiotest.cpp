#include "qiotest.h"
#include <ActiveQt/QAxWidget>
#include <QModelIndex>
#include <QModelIndexList>
#include <QItemSelectionModel>
#include <vector>
#include <QVBoxLayout>
#include <QtWidgets/qfiledialog.h>
#include "modbusModel.hpp"
#include "testProcess.hpp"

GLOBAL

using namespace std;
using namespace Drose;

QIoTest::QIoTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	gpUi = &ui;
	
	gpSignal = std::make_shared<Drose::MySignalUi>();

	gExePath = QCoreApplication::applicationDirPath();
	

	//modbus init
	gpModbusDevice = std::make_shared<QModbusTcpClient>(this);

	const QUrl url = QUrl::fromUserInput("192.168.1.55:502");
	gpModbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
	gpModbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());

	gpModbusDevice->setTimeout(1000);
	gpModbusDevice->setNumberOfRetries(3);

	if (!gpModbusDevice->connectDevice())
	{
		statusBar()->showMessage(tr("Connect failed: ") + gpModbusDevice->errorString());
	}
	
	connect(gpModbusDevice.get(), &QModbusClient::errorOccurred, [this](QModbusDevice::Error) {
		statusBar()->showMessage(gpModbusDevice->errorString(), 5000);
	});

	
	//
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
		selfCheck();
	});

	connect(ui.pushButtonLockScreen, &QPushButton::clicked, [this]() {

		QDialog tDialog;
		QLabel tLabel("Lock");
		QFont ft;
		ft.setPointSize(80);
		tLabel.setFont(ft);

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
		QFont ft;
		ft.setPointSize(80);
		mFindPointLabel->setFont(ft);
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
			gpSignal->textSignal(ui.tableWidget->item(it->rowNo, 0), "");
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 0), QColor(255, 255, 255), 0);
			/*ui.tableWidget->item(it->rowNo, 0)->setText("");
			ui.tableWidget->item(it->rowNo, 0)->setBackgroundColor(QColor(255, 255, 255));*/
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
			gpSignal->textSignal(ui.tableWidget->item(tItem.rowNo, 0), "NG");
			gpSignal->colorSignal(ui.tableWidget->item(tItem.rowNo, 0), QColor(255, 0, 0), 0);
		}
		else
		{
			gpSignal->textSignal(ui.tableWidget->item(tItem.rowNo, 0), "OK");
			gpSignal->colorSignal(ui.tableWidget->item(tItem.rowNo, 0), QColor(255, 255, 0), 0);
		}
	});

	
	//
	connect(this, SIGNAL(signalFind(QString)), this, SLOT(slotFind(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(signalFindBegin()), this, SLOT(slotFindBegin()), Qt::QueuedConnection);
	connect(ui.pushButtonStart, &QPushButton::clicked, [this]() {

		mbExit = false;
		pushButtonReadSlot();
		
	});
	connect(this, SIGNAL(signalStartList()), this, SLOT(slotStartList()));


	modbudConnectSources();

}

QIoTest::~QIoTest()
{
	
}

void QIoTest::slotFind(QString pin)
{
	mFindPointLabel->setText("Find pin: " + pin);
}

void QIoTest::findPointReady()
{
	auto reply = qobject_cast<QModbusReply *>(sender());

	if (!reply)
	{
		findRequest = true;
		return;
	}
		

	if (reply->error() == QModbusDevice::NoError)	//read success
	{
		const QModbusDataUnit unit = reply->result();
		for (uint i = 0; i < unit.valueCount(); i++)
		{
			auto value = unit.value(i);

			if (value != 0)
			{
				for (int j = 0; j < 32; j++)
				{
					if (value & 0x00000001)
					{
						signalFind(QString("%0").arg(512 * findIndex + 16 * i + j + 1));

						reply->deleteLater();
						findRequest = true;
						return;
					}
						
					value = value >> 1;
				}
			}

			if (i == unit.valueCount() - 1)
			{
				//signalFind(QString("%0").arg(""));
			}
		}
	}
	else if (reply->error() == QModbusDevice::ProtocolError)
	{
		statusBar()->showMessage(tr("Read response error: %1 (Mobus exception: 0x%2)").
			arg(reply->errorString()).
			arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
	}
	else
	{
		statusBar()->showMessage(tr("Read response error: %1 (code: 0x%2)").
			arg(reply->errorString()).
			arg(reply->error(), -1, 16), 5000);
	}

	reply->deleteLater();
	findRequest = true;
}

void QIoTest::slotFindBegin()
{
	while (true)
	{
		if (findRequest)
		{
			if (findIndex > 0)
			{
				findIndex = 0;
			}
			else
			{
				findIndex = 1;
			}

			if (auto *reply = gpModbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::RegisterType::HoldingRegisters, 164 + 32 * findIndex, 32), 40001))
			{
				if (!reply->isFinished())
				{
					connect(reply, &QModbusReply::finished, this, &QIoTest::findPointReady);
					findRequest = false;
				}
				else
					delete reply; // broadcast replies return immediately
			}
			else
			{
				statusBar()->showMessage(tr("slotReadAll error: ") + gpModbusDevice->errorString(), 5000);
			}
		}

		QApplication::processEvents();
	}
}

