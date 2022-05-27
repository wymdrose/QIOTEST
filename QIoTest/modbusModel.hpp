#include "qiotest.h"

#define ReadTimes	    20
#define ReadOnceCount	50


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

	for (size_t i = 0; i < mValuse.length(); i++)
	{
		if (mValuse[i] == 0)	//invoid
		{
			continue;
		}

		updateSets(modbusSets, i, mValuse[i]);
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
	for (size_t i = 0; i < mValuse.length(); i++)
	{
		auto val = mValuse[i];
	}

}

void QIoTest::readReady()
{
	auto reply = qobject_cast<QModbusReply *>(sender());

	if (!reply)
		return;

	if (reply->error() == QModbusDevice::NoError)
	{
		const QModbusDataUnit unit = reply->result();
		for (uint i = 0; i < unit.valueCount(); i++)
		{
			mValuse.append(unit.value(i));
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

	if (mValuse.length() >= ReadTimes * ReadOnceCount)
	{
		statusBar()->showMessage(tr("signalValuesReady."));
		signalValuesReady();
	}

}

void QIoTest::slotReadAll()
{
	mValuse.clear();

	for (size_t i = 0; i < ReadTimes; i++)
	{
		Sleep(20);
		statusBar()->clearMessage();

		if (auto *reply = gpModbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::RegisterType::HoldingRegisters, 244 + ReadOnceCount * i, ReadOnceCount), 40001))
		{
			if (!reply->isFinished())
				connect(reply, &QModbusReply::finished, this, &QIoTest::readReady);
			else
				delete reply; // broadcast replies return immediately
		}
		else
		{
			statusBar()->showMessage(tr("slotReadAll error: ") + gpModbusDevice->errorString(), 5000);
		}
	}
}

void QIoTest::slotCheckModbus()
{

	if (auto *reply = gpModbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::RegisterType::HoldingRegisters, 1, 1), 40001))
	{
		if (!reply->isFinished())
			connect(reply, &QModbusReply::finished, this, [this, reply]()
		{
			if (reply->error() == QModbusDevice::NoError)
			{
				statusBar()->showMessage(tr("Check state ready."));
				signalReadAll();
			}
			else if (reply->error() == QModbusDevice::ProtocolError)
			{
				statusBar()->showMessage(tr("slotCheckModbus Read response error: %1 (Mobus exception: 0x%2)").
					arg(reply->errorString()).
					arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
			}
			else
			{
				statusBar()->showMessage(tr("slotCheckModbus Read response error: %1 (code: 0x%2)").
					arg(reply->errorString()).
					arg(reply->error(), -1, 16), 5000);
			}
			reply->deleteLater();
		});
		else
			reply->deleteLater();
	}
	else
	{
		statusBar()->showMessage(tr("slotCheckModbus Read error: ") + gpModbusDevice->errorString(), 5000);
	}

}


void QIoTest::pushButtonReadSlot()
{
	auto writeUnit = QModbusDataUnit(QModbusDataUnit::RegisterType::HoldingRegisters, 0, 1);
	writeUnit.setValue(0, 1);
	if (auto *reply = gpModbusDevice->sendWriteRequest(writeUnit, 40001))
	{
		if (!reply->isFinished())
		{
			connect(reply, &QModbusReply::finished, this, [this, reply]()
			{
				if (reply->error() == QModbusDevice::ProtocolError)
				{
					statusBar()->showMessage(tr("Write response error: %1 (Mobus exception: 0x%2)")
						.arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),
						5000);
				}
				else if (reply->error() != QModbusDevice::NoError)
				{
					statusBar()->showMessage(tr("Write response error: %1 (code: 0x%2)").
						arg(reply->errorString()).arg(reply->error(), -1, 16), 5000);
				}
				else if (reply->error() == QModbusDevice::NoError)
				{
					signalCheckModbus();	//write success
				}
				reply->deleteLater();
			});
		}
		else
		{
			// broadcast replies return immediately
			reply->deleteLater();
		}
	}
	else
	{
		statusBar()->showMessage(tr("Write error: ") + gpModbusDevice->errorString(), 5000);
	}
}

void QIoTest::pushButtonConnectSlot()
{
	if (gpModbusDevice->state() == QModbusDevice::State::ConnectedState)
	{
		statusBar()->showMessage(tr("Connected"));
		return;
	}

	if (!gpModbusDevice->connectDevice())
	{
		statusBar()->showMessage(tr("Connect failed: ") + gpModbusDevice->errorString());
	}
}

void QIoTest::modbudConnectSources()
{
	connect(ui.pushButtonConnect, &QPushButton::clicked, [this]() {
		pushButtonConnectSlot();
	});
	connect(ui.pushButtonRead, &QPushButton::clicked, [this]() {
		pushButtonConnectSlot();
		pushButtonReadSlot();
	});

	connect(this, SIGNAL(signalValuesReady()), this, SLOT(slotValuesReady()));
	connect(this, SIGNAL(signalCheckModbus()), this, SLOT(slotCheckModbus()));
	connect(this, SIGNAL(signalReadAll()), this, SLOT(slotReadAll()));
}