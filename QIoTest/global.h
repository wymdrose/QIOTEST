
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qiotest.h"
#include <windows.h>
#include <memory>
#include <mytimer.h>
#include <mysignal.h>
#include <filelib.h>
#include <QPushButton>
#include <QGroupBox>
#include "D:/DROSE/Libhpp/mythread.hpp"
#include "D:/DROSE/Libhpp/__communicateLib.hpp"
#include <QProcess>
#include <QSettings>
#include <mysqlite.h>
#include <xlsxfile.h>
#include <QtSql\QSqlTableModel>
#include <dologs.h>
#include <QtSerialBus/QModbusDataUnit>
#include <QtSerialBus/QModbusTcpClient>

#pragma comment(lib, "Qt5Networkd.lib")
#pragma comment(lib, "Qt5SerialPortd.lib")
#pragma comment(lib, "Qt5Widgetsd.lib")
#pragma comment(lib, "Qt5SerialBusd.lib")

#pragma comment(lib, "MySignal.lib")
#pragma comment(lib, "FileLib.lib")
#pragma comment(lib, "scansn.lib")
#pragma comment(lib, "xmlwidget.lib")
#pragma comment(lib, "mysqlite.lib")
#pragma comment(lib, "xlsxFile.lib")
#pragma comment(lib, "mytimer.lib")
#pragma comment(lib, "dologs.lib")

extern  Ui::QIoTestClass* gpUi;
extern  QString gExePath;
extern  std::shared_ptr<Drose::MySignalUi> gpSignal;
extern  std::shared_ptr<Drose::Mytimer> gpMytimer;
extern  std::vector<QStringList> ipVector;
extern  std::vector<CommunicateClass::TcpClient*> gpTcpClientVector;
extern  std::vector<Drose::WorkerThread*> gpIoThreadVector;
extern  std::shared_ptr<DatabaseCover::MySqLite> gpDoSqlite;
extern  std::shared_ptr<QModbusClient> gpModbusDevice;

#define GLOBAL \
Ui::QIoTestClass* gpUi;\
QString gExePath;\
std::shared_ptr<Drose::MySignalUi> gpSignal;\
std::shared_ptr<Drose::Mytimer> gpMytimer;\
std::vector<QStringList> ipVector;\
std::vector<CommunicateClass::TcpClient*> gpTcpClientVector;\
std::vector<Drose::WorkerThread*> gpIoThreadVector;\
std::shared_ptr<DatabaseCover::MySqLite> gpDoSqlite;\
std::shared_ptr<QModbusClient> gpModbusDevice;