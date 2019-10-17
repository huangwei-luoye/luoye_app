#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include "UtilityClasses/CQssFileAdaption.h"
#include "LogOpreate/LogOperateWidget.h"
#include "GUI/CUdpCommunication.h"
#include "UtilityClasses/CSetting.h"
#include "ControlSercice/DeviceController.h"
#include "GUI/QcharWiget.h"
#include "UtilityClasses/CTools.h"
#include <QDesktopWidget>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    bool ret = CSetting::getInstance()->init("./config/config.xml");
    if(!ret)
    {
        QMessageBox::warning(this,tr("警告"),tr("加载配置文件失败"));
        LogOperate::getinstance()->LogOperaterUi("初始化配置文件config.xml失败");
    }
    QTimer::singleShot(500, this, SLOT(initNetwork()));
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{

    QVBoxLayout *pVBoxLayout = new QVBoxLayout(ui->widget_log);

    LogOperateWidget *pLogWidget = new LogOperateWidget;
    pVBoxLayout->addWidget(pLogWidget);
    ui->widget_log->setLayout(pVBoxLayout);

    pVBoxLayout = new QVBoxLayout(ui->widget_udpCommunication);
    CUdpCommunication *pCudpCommunication = new CUdpCommunication;
    pVBoxLayout->addWidget(pCudpCommunication);
    ui->widget_udpCommunication->setLayout(pVBoxLayout);

    pVBoxLayout = new QVBoxLayout(ui->widget_waveShow);
    QcharWiget *pCharwiget = QcharWiget::getInstance();
    pVBoxLayout->addWidget(pCharwiget);
    ui->widget_waveShow->setLayout(pVBoxLayout);

    QFile styleSheet(CQssFileAdaption::getInstance()->getMainWindow());
    if(styleSheet.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(styleSheet.readAll());
    }
}

void MainWindow::initNetwork()
{
    DeviceController *pDeviceContrl = DeviceController::getInstance();

    //LogOperate::getinstance()->LogOperaterUi(tr("正在初始化UDP网络中...."));
    //CTools::Delay(500);
    bool ret = pDeviceContrl->OpenTdsBoardUdp(CSetting::getInstance()->getLocalIp(),CSetting::getInstance()->getLocalPort());
    ret ? LogOperate::getinstance()->LogOperaterUi("初始化TDS板UDP网络成功") : LogOperate::getinstance()->LogOperaterUi("初始化UDP网络失败!",LOG_ERROR);
}
