/********************************************************************************
** Form generated from reading UI file 'qiotest.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QIOTEST_H
#define UI_QIOTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QIoTestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_11;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_18;
    QGridLayout *gridLayout_14;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_19;
    QGridLayout *gridLayout_16;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QLabel *labelResult;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonPause;
    QPushButton *pushButtonExit;
    QPushButton *pushButtonStepTest;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelCoordinateL;
    QLabel *label_7;
    QLabel *labelCoordinateR;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelPinL;
    QSpacerItem *horizontalSpacer;
    QLabel *labelPinR;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_5;
    QLabel *labelCategory;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEdit_coor;
    QPushButton *btn_find_coor;
    QLineEdit *lineEdit_pin;
    QPushButton *btn_find_pin;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_12;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout_13;
    QTableWidget *tableWidgetNg;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_9;
    QPushButton *pushButtonMoveUp;
    QPushButton *pushButtonMoveDown;
    QPushButton *pushButtonMoveUp_a;
    QPushButton *pushButtonMoveDown_a;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QListWidget *listWidgetUp;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_3;
    QListWidget *listWidgetDown;
    QGridLayout *gridLayout_17;
    QLabel *label;
    QLineEdit *lineEdit_login;
    QPushButton *pushButtonOpenFile;
    QLineEdit *lineEdit_path;
    QPushButton *pushButtonFindpoint;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonSelfCheck;
    QPushButton *pushButtonLockScreen;
    QComboBox *comboBox;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonRead;
    QPushButton *pushButton_11;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QIoTestClass)
    {
        if (QIoTestClass->objectName().isEmpty())
            QIoTestClass->setObjectName(QStringLiteral("QIoTestClass"));
        QIoTestClass->resize(1236, 784);
        centralWidget = new QWidget(QIoTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_11 = new QGridLayout(centralWidget);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));

        gridLayout_11->addLayout(verticalLayout_4, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        gridLayout_10 = new QGridLayout(groupBox);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_18 = new QGridLayout();
        gridLayout_18->setSpacing(6);
        gridLayout_18->setObjectName(QStringLiteral("gridLayout_18"));
        gridLayout_14 = new QGridLayout();
        gridLayout_14->setSpacing(6);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_19 = new QGridLayout(groupBox_2);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        gridLayout_16 = new QGridLayout();
        gridLayout_16->setSpacing(6);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        labelResult = new QLabel(groupBox_4);
        labelResult->setObjectName(QStringLiteral("labelResult"));
        labelResult->setFrameShape(QFrame::Panel);

        gridLayout_4->addWidget(labelResult, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButtonStart = new QPushButton(groupBox_2);
        pushButtonStart->setObjectName(QStringLiteral("pushButtonStart"));
        pushButtonStart->setAutoDefault(false);
        pushButtonStart->setFlat(false);

        horizontalLayout_4->addWidget(pushButtonStart);

        pushButtonPause = new QPushButton(groupBox_2);
        pushButtonPause->setObjectName(QStringLiteral("pushButtonPause"));
        pushButtonPause->setEnabled(false);
        pushButtonPause->setAutoDefault(false);
        pushButtonPause->setFlat(false);

        horizontalLayout_4->addWidget(pushButtonPause);

        pushButtonExit = new QPushButton(groupBox_2);
        pushButtonExit->setObjectName(QStringLiteral("pushButtonExit"));
        pushButtonExit->setAutoDefault(false);
        pushButtonExit->setFlat(false);

        horizontalLayout_4->addWidget(pushButtonExit);

        pushButtonStepTest = new QPushButton(groupBox_2);
        pushButtonStepTest->setObjectName(QStringLiteral("pushButtonStepTest"));
        pushButtonStepTest->setEnabled(true);
        pushButtonStepTest->setAutoDefault(false);
        pushButtonStepTest->setFlat(false);

        horizontalLayout_4->addWidget(pushButtonStepTest);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        gridLayout_6 = new QGridLayout(groupBox_5);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelCoordinateL = new QLabel(groupBox_5);
        labelCoordinateL->setObjectName(QStringLiteral("labelCoordinateL"));
        labelCoordinateL->setFrameShape(QFrame::Box);

        horizontalLayout_2->addWidget(labelCoordinateL);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setPixmap(QPixmap(QString::fromUtf8("Arrow.png")));

        horizontalLayout_2->addWidget(label_7);

        labelCoordinateR = new QLabel(groupBox_5);
        labelCoordinateR->setObjectName(QStringLiteral("labelCoordinateR"));
        labelCoordinateR->setFrameShape(QFrame::Box);

        horizontalLayout_2->addWidget(labelCoordinateR);


        gridLayout_6->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        gridLayout_7 = new QGridLayout(groupBox_6);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelPinL = new QLabel(groupBox_6);
        labelPinL->setObjectName(QStringLiteral("labelPinL"));
        labelPinL->setFrameShape(QFrame::Box);

        horizontalLayout_3->addWidget(labelPinL);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        labelPinR = new QLabel(groupBox_6);
        labelPinR->setObjectName(QStringLiteral("labelPinR"));
        labelPinR->setFrameShape(QFrame::Box);

        horizontalLayout_3->addWidget(labelPinR);


        gridLayout_7->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(groupBox_2);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        gridLayout_5 = new QGridLayout(groupBox_7);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        labelCategory = new QLabel(groupBox_7);
        labelCategory->setObjectName(QStringLiteral("labelCategory"));
        labelCategory->setFrameShape(QFrame::Box);

        gridLayout_5->addWidget(labelCategory, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_7);


        horizontalLayout_6->addLayout(verticalLayout);


        gridLayout_8->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lineEdit_coor = new QLineEdit(groupBox_2);
        lineEdit_coor->setObjectName(QStringLiteral("lineEdit_coor"));
        lineEdit_coor->setEnabled(true);
        lineEdit_coor->setLayoutDirection(Qt::LeftToRight);
        lineEdit_coor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lineEdit_coor);

        btn_find_coor = new QPushButton(groupBox_2);
        btn_find_coor->setObjectName(QStringLiteral("btn_find_coor"));
        btn_find_coor->setEnabled(true);

        horizontalLayout_5->addWidget(btn_find_coor);

        lineEdit_pin = new QLineEdit(groupBox_2);
        lineEdit_pin->setObjectName(QStringLiteral("lineEdit_pin"));
        lineEdit_pin->setEnabled(true);
        lineEdit_pin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lineEdit_pin);

        btn_find_pin = new QPushButton(groupBox_2);
        btn_find_pin->setObjectName(QStringLiteral("btn_find_pin"));
        btn_find_pin->setEnabled(true);

        horizontalLayout_5->addWidget(btn_find_pin);


        gridLayout_8->addLayout(horizontalLayout_5, 1, 0, 1, 1);


        gridLayout_16->addLayout(gridLayout_8, 0, 0, 1, 1);

        tabWidget = new QTabWidget(groupBox_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_12 = new QGridLayout(tab);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        tableWidget = new QTableWidget(tab);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        gridLayout_12->addWidget(tableWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_13 = new QGridLayout(tab_2);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        tableWidgetNg = new QTableWidget(tab_2);
        tableWidgetNg->setObjectName(QStringLiteral("tableWidgetNg"));
        tableWidgetNg->setSelectionBehavior(QAbstractItemView::SelectRows);

        gridLayout_13->addWidget(tableWidgetNg, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_16->addWidget(tabWidget, 1, 0, 1, 1);

        gridLayout_16->setRowStretch(0, 4);
        gridLayout_16->setRowStretch(1, 6);

        gridLayout_19->addLayout(gridLayout_16, 0, 0, 1, 1);


        gridLayout_14->addWidget(groupBox_2, 0, 0, 1, 1);

        gridLayout_15 = new QGridLayout();
        gridLayout_15->setSpacing(6);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        pushButtonMoveUp = new QPushButton(groupBox);
        pushButtonMoveUp->setObjectName(QStringLiteral("pushButtonMoveUp"));
        pushButtonMoveUp->setLayoutDirection(Qt::LeftToRight);

        gridLayout_9->addWidget(pushButtonMoveUp, 0, 0, 1, 1);

        pushButtonMoveDown = new QPushButton(groupBox);
        pushButtonMoveDown->setObjectName(QStringLiteral("pushButtonMoveDown"));
        pushButtonMoveDown->setLayoutDirection(Qt::LeftToRight);

        gridLayout_9->addWidget(pushButtonMoveDown, 0, 1, 1, 1);

        pushButtonMoveUp_a = new QPushButton(groupBox);
        pushButtonMoveUp_a->setObjectName(QStringLiteral("pushButtonMoveUp_a"));
        pushButtonMoveUp_a->setLayoutDirection(Qt::LeftToRight);

        gridLayout_9->addWidget(pushButtonMoveUp_a, 0, 2, 1, 1);

        pushButtonMoveDown_a = new QPushButton(groupBox);
        pushButtonMoveDown_a->setObjectName(QStringLiteral("pushButtonMoveDown_a"));
        pushButtonMoveDown_a->setLayoutDirection(Qt::LeftToRight);

        gridLayout_9->addWidget(pushButtonMoveDown_a, 0, 3, 1, 1);


        gridLayout_15->addLayout(gridLayout_9, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        listWidgetUp = new QListWidget(groupBox_3);
        listWidgetUp->setObjectName(QStringLiteral("listWidgetUp"));
        listWidgetUp->setStyleSheet(QStringLiteral("color: rgb(0, 85, 0);"));

        gridLayout_2->addWidget(listWidgetUp, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_8 = new QGroupBox(groupBox);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        gridLayout_3 = new QGridLayout(groupBox_8);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        listWidgetDown = new QListWidget(groupBox_8);
        listWidgetDown->setObjectName(QStringLiteral("listWidgetDown"));
        listWidgetDown->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(listWidgetDown, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_8, 2, 0, 1, 1);


        gridLayout_14->addLayout(gridLayout_15, 0, 1, 1, 1);

        gridLayout_14->setColumnStretch(0, 7);
        gridLayout_14->setColumnStretch(1, 3);

        gridLayout_18->addLayout(gridLayout_14, 1, 0, 1, 1);

        gridLayout_17 = new QGridLayout();
        gridLayout_17->setSpacing(6);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_17->addWidget(label, 0, 0, 1, 1);

        lineEdit_login = new QLineEdit(groupBox);
        lineEdit_login->setObjectName(QStringLiteral("lineEdit_login"));

        gridLayout_17->addWidget(lineEdit_login, 0, 1, 1, 1);

        pushButtonOpenFile = new QPushButton(groupBox);
        pushButtonOpenFile->setObjectName(QStringLiteral("pushButtonOpenFile"));

        gridLayout_17->addWidget(pushButtonOpenFile, 0, 2, 1, 1);

        lineEdit_path = new QLineEdit(groupBox);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));

        gridLayout_17->addWidget(lineEdit_path, 0, 3, 1, 1);

        pushButtonFindpoint = new QPushButton(groupBox);
        pushButtonFindpoint->setObjectName(QStringLiteral("pushButtonFindpoint"));

        gridLayout_17->addWidget(pushButtonFindpoint, 0, 4, 1, 1);

        pushButtonEdit = new QPushButton(groupBox);
        pushButtonEdit->setObjectName(QStringLiteral("pushButtonEdit"));
        pushButtonEdit->setEnabled(false);

        gridLayout_17->addWidget(pushButtonEdit, 0, 5, 1, 1);

        pushButtonSave = new QPushButton(groupBox);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));
        pushButtonSave->setEnabled(false);

        gridLayout_17->addWidget(pushButtonSave, 0, 6, 1, 1);

        pushButtonSelfCheck = new QPushButton(groupBox);
        pushButtonSelfCheck->setObjectName(QStringLiteral("pushButtonSelfCheck"));

        gridLayout_17->addWidget(pushButtonSelfCheck, 0, 7, 1, 1);

        pushButtonLockScreen = new QPushButton(groupBox);
        pushButtonLockScreen->setObjectName(QStringLiteral("pushButtonLockScreen"));

        gridLayout_17->addWidget(pushButtonLockScreen, 0, 8, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_17->addWidget(comboBox, 0, 9, 1, 1);

        pushButtonConnect = new QPushButton(groupBox);
        pushButtonConnect->setObjectName(QStringLiteral("pushButtonConnect"));

        gridLayout_17->addWidget(pushButtonConnect, 0, 10, 1, 1);

        pushButtonRead = new QPushButton(groupBox);
        pushButtonRead->setObjectName(QStringLiteral("pushButtonRead"));

        gridLayout_17->addWidget(pushButtonRead, 0, 11, 1, 1);

        pushButton_11 = new QPushButton(groupBox);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setEnabled(false);

        gridLayout_17->addWidget(pushButton_11, 0, 12, 1, 1);


        gridLayout_18->addLayout(gridLayout_17, 0, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_18, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout_11->addLayout(gridLayout, 1, 1, 1, 1);

        QIoTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QIoTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1236, 26));
        QIoTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QIoTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QIoTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QIoTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QIoTestClass->setStatusBar(statusBar);

        retranslateUi(QIoTestClass);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QIoTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QIoTestClass)
    {
        QIoTestClass->setWindowTitle(QApplication::translate("QIoTestClass", "QIoTest", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("QIoTestClass", "\347\252\227\345\217\243\345\212\237\350\203\275\345\214\272", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("QIoTestClass", "\346\265\213\350\257\225\347\252\227\345\217\243", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("QIoTestClass", "ok/ng", Q_NULLPTR));
        labelResult->setText(QString());
        pushButtonStart->setText(QApplication::translate("QIoTestClass", "\345\274\200\345\247\213", Q_NULLPTR));
        pushButtonPause->setText(QApplication::translate("QIoTestClass", "\346\232\202\345\201\234", Q_NULLPTR));
        pushButtonExit->setText(QApplication::translate("QIoTestClass", "\351\200\200\345\207\272\346\265\213", Q_NULLPTR));
        pushButtonStepTest->setText(QApplication::translate("QIoTestClass", "\345\215\225\346\255\245\346\265\213", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("QIoTestClass", "\345\235\220\346\240\207", Q_NULLPTR));
        labelCoordinateL->setText(QString());
        label_7->setText(QString());
        labelCoordinateR->setText(QString());
        groupBox_6->setTitle(QApplication::translate("QIoTestClass", "\351\222\210\347\202\271", Q_NULLPTR));
        labelPinL->setText(QString());
        labelPinR->setText(QString());
        groupBox_7->setTitle(QApplication::translate("QIoTestClass", "\345\233\276\345\217\267", Q_NULLPTR));
        labelCategory->setText(QString());
        lineEdit_coor->setText(QString());
        btn_find_coor->setText(QApplication::translate("QIoTestClass", "\345\235\220\346\240\207\346\237\245", Q_NULLPTR));
        btn_find_pin->setText(QApplication::translate("QIoTestClass", "\351\222\210\347\202\271\346\237\245", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QIoTestClass", "\346\265\213\350\257\225\346\241\243\346\241\210", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QIoTestClass", "NG\350\256\260\345\275\225", Q_NULLPTR));
        pushButtonMoveUp->setText(QApplication::translate("QIoTestClass", "/\\ \n"
"|", Q_NULLPTR));
        pushButtonMoveDown->setText(QApplication::translate("QIoTestClass", "|\n"
"\\/", Q_NULLPTR));
        pushButtonMoveUp_a->setText(QApplication::translate("QIoTestClass", "/\\\n"
"||", Q_NULLPTR));
        pushButtonMoveDown_a->setText(QApplication::translate("QIoTestClass", "||\n"
"\\/", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("QIoTestClass", "\346\265\213\350\257\225\345\233\276\345\217\267", Q_NULLPTR));
        groupBox_8->setTitle(QApplication::translate("QIoTestClass", "\346\241\243\346\241\210\345\233\276\345\217\267", Q_NULLPTR));
        label->setText(QApplication::translate("QIoTestClass", "\347\231\273\351\231\206\350\264\246\345\217\267:", Q_NULLPTR));
        pushButtonOpenFile->setText(QApplication::translate("QIoTestClass", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        pushButtonFindpoint->setText(QApplication::translate("QIoTestClass", "\346\211\276\347\202\271", Q_NULLPTR));
        pushButtonEdit->setText(QApplication::translate("QIoTestClass", "\344\277\256\346\224\271on/off", Q_NULLPTR));
        pushButtonSave->setText(QApplication::translate("QIoTestClass", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButtonSelfCheck->setText(QApplication::translate("QIoTestClass", "\350\207\252\346\243\200", Q_NULLPTR));
        pushButtonLockScreen->setText(QApplication::translate("QIoTestClass", "\351\224\201\345\256\232", Q_NULLPTR));
        pushButtonConnect->setText(QApplication::translate("QIoTestClass", "Connect", Q_NULLPTR));
        pushButtonRead->setText(QApplication::translate("QIoTestClass", "Read", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("QIoTestClass", "\347\263\273\347\273\237\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QIoTestClass: public Ui_QIoTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QIOTEST_H
