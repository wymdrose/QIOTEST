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

bool QIoTest::selfCheck()
{

	for (const auto& item : com_pairs_)
	{
		auto val_p = std::vector<uint16_t>(item.begin(), item.end());
		if (val_p.size() != 2)
		{
			qDebug() << QString("error: val_p.size()") << "\r";
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
	ui.labelResult->clear();
	if (mListTest.size() < 1)
	{
		QMessageBox::information(this, "", "请先加载测试档案！");
		gpSignal->colorSignal(gpUi->pushButtonStart, "QPushButton{background:}");
		ui.pushButtonStart->setEnabled(true);
		return;
	}

	bool result = true;

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

		ui.tableWidget->selectRow(it->rowNo);
		ui.tableWidget->setFocus();

		if (!lineTest(*it))
		{
			result = false;
			ui.labelCoordinateL->setText(it->coordinateL);
			ui.labelCoordinateR->setText(it->coordinateR);
			ui.labelPinL->setText(it->pinL);
			ui.labelPinR->setText(it->pinR);
			ui.labelCategory->setText(it->category);

			gpSignal->textSignal(ui.tableWidget->item(it->rowNo, 0), "NG");
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 0), QColor(255, 0, 0), 0);
		
			/*if (QMessageBox::question(this, "", " 继续 ?") != QMessageBox::Yes)
				break;*/
		}
		else
		{
			ui.tableWidget->item(it->rowNo, 0)->setText("OK");
			ui.tableWidget->item(it->rowNo, 0)->setBackgroundColor(QColor(0, 255, 0));
		}
	}

	if (!result)
	{
		ui.labelResult->setText(QStringLiteral("<font style='font-size:50px; color:red;'>NG</font>"));
	}
	else
	{
		ui.labelResult->setText(QStringLiteral("<font style='font-size:50px; color:green;'>OK</font>"));
	}

	gpSignal->colorSignal(gpUi->pushButtonStart, "QPushButton{background:}");
	ui.pushButtonStart->setEnabled(true);
}
