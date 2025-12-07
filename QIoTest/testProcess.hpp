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
				lineMsg_ = QObject::tr("短路:") + QString("%0 - %1").arg(L).arg(R);
				for (const auto& pin : item)
				{
					lineMsg_ += QString(",%0").arg(pin);
				}

				return false;	//short
			}
		}
	}

	return true;
}

bool QIoTest::checkPins(itemTest item)
{
	lineMsg_.clear();

	int L = item.pinL.toInt();
	int R = item.pinR.toInt();

	int index;
	for (index = 0; index < modbusSets.length(); index++)
	{
		auto&& item = modbusSets[index];

		if (item.contains(L) && item.contains(R))
		{
			if (enShort_ && !checkShort(item, L, R))
			{
				return false;	//short
			}

			break;
		}
	}

	if (index >= modbusSets.length())
	{
		lineMsg_ = QString("NG: %0 - %1").arg(L).arg(R);
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
		QMessageBox::information(this, "", QObject::tr("请先加载测试档案！"));
		gpSignal->colorSignal(gpUi->pushButtonStart, "QPushButton{background:}");
		ui.pushButtonStart->setEnabled(true);
		return;
	}

	bool result = true;

	ng_list_.clear();
	gpUi->tableWidgetNg->clear();
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

		ui.labelCoordinateL->setText(it->coordinateL);
		ui.labelCoordinateR->setText(it->coordinateR);
		ui.labelPinL->setText(it->pinL);
		ui.labelPinR->setText(it->pinR);
		ui.labelCategory->setText(it->category);

		if (!lineTest(*it))
		{
			result = false;

			gpSignal->textSignal(ui.tableWidget->item(it->rowNo, 0), "  NG  ");
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 0), QColor(255, 0, 0), 0);
			/*gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 1), QColor(255, 0, 0), 0);
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 2), QColor(255, 0, 0), 0);
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 3), QColor(255, 0, 0), 0);
			gpSignal->colorSignal(ui.tableWidget->item(it->rowNo, 4), QColor(255, 0, 0), 0);*/

			ui.labelResult->setText(QStringLiteral("<font style='font-size:40px; color:red;'>%0</font>").arg(lineMsg_));

			ng_list_.append(*it);

			/*if (QMessageBox::question(this, "", " 继续 ?") != QMessageBox::Yes)
				break;*/
		}
		else
		{
			ui.tableWidget->item(it->rowNo, 0)->setText("  OK  ");
			ui.tableWidget->item(it->rowNo, 0)->setBackgroundColor(QColor(0, 255, 0));
			/*ui.tableWidget->item(it->rowNo, 1)->setBackgroundColor(QColor(0, 255, 0));
			ui.tableWidget->item(it->rowNo, 2)->setBackgroundColor(QColor(0, 255, 0));
			ui.tableWidget->item(it->rowNo, 3)->setBackgroundColor(QColor(0, 255, 0));
			ui.tableWidget->item(it->rowNo, 4)->setBackgroundColor(QColor(0, 255, 0));*/
		}
	}

	//ng list show
	gpUi->tableWidgetNg->setRowCount(ng_list_.count());
	gpUi->tableWidgetNg->setColumnCount(10);
	for (size_t i = 0; i < ng_list_.count(); i++)
	{
		int index = 0;
		
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem("  NG  ").clone());
		ui.tableWidgetNg->item(i, 0)->setTextColor(QColor(255, 0, 0));
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem(ng_list_[i].coordinateL).clone());
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem(ng_list_[i].coordinateR).clone());
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem(ng_list_[i].category).clone());
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem("").clone());
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem("").clone());
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem("").clone());
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem("").clone());
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem(ng_list_[i].pinL).clone());
		gpUi->tableWidgetNg->setItem(i, index++, QTableWidgetItem(ng_list_[i].pinR).clone());
	}
	gpUi->tableWidgetNg->resizeColumnsToContents();


	//
	if (result)
	{
		ui.labelResult->setText(QStringLiteral("<font style='font-size:40px; color:green;'>OK</font>"));
	}

	gpUi->tableWidget->resizeColumnsToContents();
	gpSignal->colorSignal(gpUi->pushButtonStart, "QPushButton{background:}");
	ui.pushButtonStart->setEnabled(true);
}
