#include "qiotest.h"

bool QIoTest::checkShort(QSet<int> item, int L, int R)
{
	for (auto&& set : testTaskSets)
	{
		if (set.contains(L) && set.contains(R))
		{
			item.remove(L);
			item.remove(R);

			if (!set.contains(item))	//modbus set > test set
			{
				return false;	//short
			}
		}
	}

	return true;
}

bool QIoTest::checkPins(itemTest item)
{
	int L = item.pinL.toInt();
	int R = item.pinR.toInt();

	int index;
	for (index = 0; index < modbusSets.length(); index++)
	{
		auto&& item = modbusSets[index];

		if (item.contains(L) && item.contains(R))
		{
			if (!checkShort(item, L, R))
			{
				return false;	//short
			}

			break;
		}
	}

	if (index >= modbusSets.length())
	{
		return false;	//disconnect
	}

	return true;
}

bool QIoTest::selfCheck()	//check value > index
{
	for (size_t i = 0; i < mValuse.length(); i++)
	{
		if (mValuse[i] != 0 && mValuse[i] < i + 1)
		{
			qDebug() << QString("error: %0 and %1").arg(i + 1).arg(mValuse[i]) << "\r";
			return false;
		}
	}

	return true;
}


bool QIoTest::lineTest(itemTest item)
{
	if (!checkPins(item))
	{
		return false;
	}

	return true;
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
			//	ui.labelResult->setText("NG");
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
