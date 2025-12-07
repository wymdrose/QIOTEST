#include "qiotest.h"
#include <ActiveQt/QAxWidget>
#include <QModelIndex>
#include <QModelIndexList>
#include <QItemSelectionModel>
#include <vector>
#include <QVBoxLayout>
#include <QtWidgets/qfiledialog.h>
#include "QtMultimedia/qsound.h"
#include "modbusModel.hpp"
#include "testProcess.hpp"

GLOBAL

using namespace std;
using namespace Drose;

QIoTest::QIoTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setWindowTitle(QStringLiteral("导通检测仪  本机扫描总点数=1024  软件版本v3.0.7  东莞精伟智能"));
	
	gpUi = &ui;
	
	gpSignal = std::make_shared<Drose::MySignalUi>();

	gExePath = QCoreApplication::applicationDirPath();
	
	gpUi->tabWidget->setCurrentIndex(0);
	gpUi->tableWidget->horizontalHeader()->setVisible(false);
	gpUi->tableWidget->verticalHeader()->setVisible(false);
	gpUi->tableWidgetNg->horizontalHeader()->setVisible(false);
	gpUi->tableWidgetNg->verticalHeader()->setVisible(false);

	// com init
	for (size_t i = 0; i < 10; i++)
	{
		gpUi->comboBox->addItem(QString("Com %0").arg(i));
	}
	auto com = settings.value("com_port").toInt();
	gpUi->comboBox->setCurrentIndex(com);
	gpComClient = std::make_shared<CommunicateClass::ComPortOne>(com);
	gpComClient->init();


	
	//
	connect(ui.comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this]{
		settings.setValue("com_port", ui.comboBox->currentIndex());
	});

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
	
	connect(ui.pushButtonMoveUp_a, &QPushButton::clicked, [this]()
	{
		while (ui.listWidgetDown->count() > 0)
		{
			auto tItem = ui.listWidgetDown->takeItem(0);
			ui.listWidgetUp->addItem(tItem);
			mCurCategorys.insert(tItem->text());
		}

	});

	connect(ui.pushButtonMoveDown_a, &QPushButton::clicked, [this]() {
		
		while (ui.listWidgetUp->count() > 0)
		{
			auto tItem = ui.listWidgetUp->takeItem(0);
			ui.listWidgetDown->addItem(tItem);
			mCurCategorys.remove(tItem->text());
		}
	});


	connect(ui.pushButtonOpenFile, &QPushButton::clicked, [this]() {
		
		mFilePath = QFileDialog::getOpenFileName(NULL, QStringLiteral("打开文件"), 
			gExePath + "/cfg/", QString("*%0*.xlsx").arg(ui.lineEdit_login->text()));

		if (mFilePath.isEmpty())
			return;		

		ui.lineEdit_path->setText(mFilePath);

		FileIo::XlsxFile file;
		file.readExcel(mFilePath, ui.tableWidget);

		gpUi->tableWidget->resizeColumnsToContents();

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

		FileIo::XlsxFile file;
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
	connect(ui.btn_find_coor, &QPushButton::clicked, [this]() {
		auto coor = ui.lineEdit_coor->text();
		for (auto it = mListTest.begin(); it != mListTest.end(); ++it)
		{
			if (it->coordinateL == coor || it->coordinateR == coor)
			{
				ui.tableWidget->selectRow(it->rowNo);
				ui.tableWidget->setFocus();
			}
		}
	});

	connect(ui.btn_find_pin, &QPushButton::clicked, [this]() {
		auto pin = ui.lineEdit_pin->text();
		for (auto it = mListTest.begin(); it != mListTest.end(); ++it)
		{
			if (it->pinL == pin || it->pinR == pin)
			{
				ui.tableWidget->selectRow(it->rowNo);
				ui.tableWidget->setFocus();
			}
		}
	});

	connect(ui.checkBox_short, &QCheckBox::clicked, [this](bool checked) {
		if (checked)
		{
			qDebug() << "Checkbox is now checked.";
			enShort_ = true;
		}
		else
		{
			qDebug() << "Checkbox is now unchecked.";
			enShort_ = false;
		}
			
	});

	
	connect(ui.pushButtonFindpoint, &QPushButton::clicked, [this]() {

		QDialog* tpDialog = new QDialog();

		mbExit = false;
		connect(tpDialog, &QDialog::finished, [this]
		{
			mbExit = true;
		});

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
		gpSignal->colorSignal(gpUi->pushButtonStart, "QPushButton{background:}");
		ui.labelResult->clear();

		for (auto it = mListTest.begin(); it != mListTest.end(); ++it)
		{
			gpSignal->textSignal(ui.tableWidget->item(it->rowNo, 0), "");
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 0), QColor(255, 255, 255), 0);
			/*ui.tableWidget->item(it->rowNo, 0)->setText("");
			ui.tableWidget->item(it->rowNo, 0)->setBackgroundColor(QColor(255, 255, 255));*/
		}
	});
	connect(ui.pushButtonStepTest, &QPushButton::clicked, [this]() {

		ui.labelResult->clear();

		if (mListTest.size() < 1)
		{
			QMessageBox::information(this, "", QObject::tr("请先加载测试档案..."));
			gpSignal->colorSignal(gpUi->pushButtonStart, "QPushButton{background:}");
			ui.pushButtonStart->setEnabled(true);
			return;
		}

		auto widget = ui.tableWidgetNg;
		QList<QTableWidgetItem*>items = widget->selectedItems();
		if (items.count() < 1)
		{
			QMessageBox::information(this, "", QStringLiteral("请选择测试行..."));
			return;
		}

		// read
		bStep_ = true;
		ui.pushButtonRead->clicked();

		int i = widget->row(items.at(0));
		itemTest tItem;
		tItem.bInlist = true;
		tItem.result = -1;
		tItem.rowNo = i;
		tItem.coordinateL = widget->item(i, 1)->text();
		tItem.coordinateR = widget->item(i, 2)->text();
		tItem.category = widget->item(i, 3)->text();
		tItem.pinL = widget->item(i, 8)->text();
		tItem.pinR = widget->item(i, 9)->text();

		ui.labelCoordinateL->setText(tItem.coordinateL);
		ui.labelCoordinateR->setText(tItem.coordinateR);
		ui.labelPinL->setText(tItem.pinL);
		ui.labelPinR->setText(tItem.pinR);
		ui.labelCategory->setText(tItem.category);

		if (!lineTest(tItem))
		{
			gpSignal->textSignal(widget->item(tItem.rowNo, 0), "  NG  ");
			//gpSignal->colorSignal(widget->item(tItem.rowNo, 0), QColor(255, 0, 0), 0);
			widget->item(tItem.rowNo, 0)->setTextColor(QColor(255, 0, 0));
			ui.labelResult->setText(QStringLiteral("<font style='font-size:40px; color:red;'>%0</font>").arg(lineMsg_));
		}
		else
		{
			gpSignal->textSignal(widget->item(tItem.rowNo, 0), "  OK  ");
			//gpSignal->colorSignal(widget->item(tItem.rowNo, 0), QColor(0, 255, 0), 0);
			widget->item(tItem.rowNo, 0)->setTextColor(QColor(0, 255, 0));
			ui.labelResult->setText(QStringLiteral("<font style='font-size:40px; color:green;'>OK: %0 - %1</font>").arg(tItem.pinL).arg(tItem.pinR));
		}

		bStep_ = false;
	});

	connect(ui.tableWidget, &QTableWidget::itemSelectionChanged, [this](){
		auto items = ui.tableWidget->selectedItems();
		auto size = items.count();
		if (size >= 7)
		{
			ui.labelCoordinateL->setText(items[1]->text());
			ui.labelCoordinateR->setText(items[2]->text());
			ui.labelCategory->setText(items[3]->text());
			ui.labelPinL->setText(items[5]->text());
			ui.labelPinR->setText(items[6]->text());
		}
		if (size >= 10)
		{
			ui.labelPinL->setText(items[8]->text());
			ui.labelPinR->setText(items[9]->text());
		}
		
	});
	//
	connect(this, SIGNAL(signalFind(QString)), this, SLOT(slotFind(QString)));
	connect(this, SIGNAL(signalFindBegin()), this, SLOT(slotFindBegin()), Qt::QueuedConnection);
	connect(ui.pushButtonStart, &QPushButton::clicked, [this]() {

		mbExit = false;
		gpSignal->colorSignal(gpUi->pushButtonStart, "QPushButton{background:lightgreen}");

		for (auto it = mListTest.begin(); it != mListTest.end(); ++it)
		{
			gpSignal->textSignal(ui.tableWidget->item(it->rowNo, 0), " ");
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 0), QColor(255, 255, 255), 0);
			/*gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 1), QColor(255, 255, 255), 0);
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 2), QColor(255, 255, 255), 0);
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 3), QColor(255, 255, 255), 0);
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 4), QColor(255, 255, 255), 0);*/
		}

		qDebug() << "pushButtonReadSlot...";
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

void QIoTest::slotFindBegin()
{
	while (true)
	{
		_sleeploop(100);

		if (mbExit)
		{
			mbExit = false;
			break;
		}

		QByteArray recv;
		if (!gpComClient->communicate(QByteArray::fromHex("AA2800"), recv))
		{
			statusBar()->showMessage(tr("error: AA2800"), 5000);
			continue;
		}

		std::vector<uint8_t> msg(recv.begin(), recv.end());

		if (msg.size() < 3)
		{
			statusBar()->showMessage(tr("error: msg.size() < 3"), 5000);
			continue;
		}

		if (msg[0] != 0xDE)
		{
			statusBar()->showMessage(tr("error: msg[0]"), 5000);
			continue;
		}

		QStringList v_pins;

		for (size_t i = 1; i < msg.size(); i+=2)
		{
			auto pin = (((uint16_t)msg[i]) << 8) | msg[i+1];
			uint16_t pin_s = (pin / 64) * 64 + (64 - pin % 64);
			v_pins.append(QString("%0").arg(pin_s));
		}

		signalFind(v_pins.join(","));

		QSound::play(gExePath + "/find.wav");
	}
}

