#include "qiotest.h"

void QIoTest::updateSets(QVector<QSet<int>>& sets, int L, int R)
{
	int index;
	for (index = 0; index < sets.length(); index++)
	{
		auto& item = sets[index];
		if (item.contains(L) && !item.contains(R))
		{
			item.insert(R);
			break;
		}
		else if (!item.contains(L) && item.contains(R))
		{
			item.insert(L);
			break;
		}
	}
	if (index >= sets.length())
	{
		QSet<int> tSet;
		tSet.insert(L);
		tSet.insert(R);
		sets.push_back(tSet);
	}
}

void QIoTest::updateModbusSets()
{
	modbusSets.clear();

	for (const auto& item : com_pairs_)
	{
		auto val_p = std::vector<uint16_t>(item.begin(), item.end());
		if (val_p.size() < 2)
		{
			continue;
		}

		updateSets(modbusSets, val_p[0], val_p[1]);
	}

}

void QIoTest::updateTestTask()
{
	testTaskSets.clear();

	for (auto it = mListTest.begin(); it != mListTest.end(); ++it)
	{
		if (!mCurCategorys.contains(it->category))
		{
			it->bInlist = false;
			continue;
		}

		int L = it->pinL.toInt();
		int R = it->pinR.toInt();

		updateSets(testTaskSets, L, R);

	}
}


void QIoTest::slotValuesReady()
{

	updateTestTask();
	updateModbusSets();

	//
	ui.pushButtonStart->setEnabled(false);
	
	signalStartList();
	ui.labelResult->clear();
}


bool QIoTest::msgParse(bool bfirst)
{
	auto cmd = bfirst ? QByteArray::fromHex("AA2700") : QByteArray::fromHex("AA2701");

	QByteArray recv;
	if (!gpComClient->communicate(cmd, recv))
	{
		gpSignal->colorSignal(gpUi->pushButtonStart, "QPushButton{background:}");
		statusBar()->showMessage(tr("Write error: "), 5000);
		return false;
	}

	std::vector<uint8_t> msg(recv.begin(), recv.end());

	if (msg.size() < 1)
	{
		statusBar()->showMessage(tr("error: msg.size() < 1"), 5000);
		return false;
	}

	if (msg[0] != 0xDE)
	{
		statusBar()->showMessage(tr("error: msg[0]"), 5000);
		return false;
	}

	if (msg.size() > 255)
	{
		statusBar()->showMessage(tr("error: msg.size() > 255"), 5000);
		return false;
	}

	int index = 1;
	while (index < msg.size())
	{
		int cnt = msg[index];

		if (cnt == 0) // tail fill
		{
			break;
		}

		index++;
		for (int i = 0; i < cnt - 1; i++)
		{
			uint16_t first = (((uint16_t)msg[index + i]) << 8) | msg[index + i + 1];
			uint16_t second = (((uint16_t)msg[index + i + 2]) << 8) | msg[index + i + 3];
			com_pairs_.insert({ first, second });
		}
		index += cnt * 2;
	}

	if (msg.size() < 255)
	{
		parse_done_ = true;
		signalValuesReady();
	}

	return true;
}

void QIoTest::pushButtonReadSlot()
{
	
	//
	com_pairs_.clear();
	parse_done_ = false;

	if (!msgParse(true))
	{
		gpSignal->colorSignal(gpUi->pushButtonStart, "QPushButton{background:}");
		statusBar()->showMessage(tr("msgParse error: "), 5000);
		return;
	}

	for (size_t i = 0; i < 10; i++)
	{
		if (parse_done_)
		{
			break;
		}

		if (!msgParse())
		{
			return;
		}
	}

}

void QIoTest::pushButtonConnectSlot()
{
	gpComClient = std::make_shared<CommunicateClass::ComPortOne>(gpUi->comboBox->currentIndex());
	if (!gpComClient->init())
	{
		gpSignal->showDialogSignal("ConnectSlot", QStringLiteral("<font style='font-size:50px; background-color:white; color:red;'>连接失败</font>"));
		statusBar()->showMessage(tr("Connect failed: "));
		return;
	}

	gpSignal->showDialogSignal("ConnectSlot", QStringLiteral("<font style='font-size:50px; background-color:white; color:green;'>连接成功</font>"));
	statusBar()->showMessage(tr("Connected"));
	return;
}

void QIoTest::modbudConnectSources()
{
	connect(ui.pushButtonConnect, &QPushButton::clicked, [this]() {
		pushButtonConnectSlot();
	});
	connect(ui.pushButtonRead, &QPushButton::clicked, [this]() {
		pushButtonReadSlot();
	});

	connect(this, SIGNAL(signalValuesReady()), this, SLOT(slotValuesReady()));
}