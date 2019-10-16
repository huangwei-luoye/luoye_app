#include "LogOperateWidget.h"
#include "ui_LogOperateWidget.h"
#include <QDateTime>
#include <QScrollBar>
#include <QTextCodec>
//#include <global.h>
#include <QDebug>
#include "UtilityClasses/CQssFileAdaption.h"

LogOperateWidget::LogOperateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogOperateWidget),
    m_tableModel(new LogOperateTableMode), m_nCurrentClickedRow(-1)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setEnabled(false);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalScrollBar()->setSingleStep(1);
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tableView->setModel(m_tableModel);
    ui->tableView->setColumnWidth(0, 250);
    qRegisterMetaType<LogOperateLevel>("LogOperateLevel");
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(OnTableClicked(const QModelIndex &)));
    connect(LogOperate::getinstance(), SIGNAL(LogOperateUiSignal(QString,LogOperateLevel)), this, SLOT(OnAppendLogInfo(QString,LogOperateLevel)), Qt::QueuedConnection);

    QFile styleSheet(CQssFileAdaption::getInstance()->getLog());
    if(styleSheet.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(styleSheet.readAll());
    }
}

LogOperateWidget::~LogOperateWidget(void)
{
    delete ui;
    delete m_tableModel;
}

void LogOperateWidget::on_toolButton_clearAll_clicked()
{
    m_tableModel->clearData();
    m_nCurrentClickedRow = -1;
}

void LogOperateWidget::on_toolButton_delete_clicked()
{
    if (m_nCurrentClickedRow >= 0)
    {
        m_tableModel->removeRowData(m_nCurrentClickedRow);
    }
}

void LogOperateWidget::OnTableClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        m_nCurrentClickedRow = index.row();
    }
}

void LogOperateWidget::OnAppendLogInfo(QString strLogInfo, LogOperateLevel level)
{
    ui->tableView->scrollToBottom();

    LogOperateData *data = new LogOperateData();
    data->dateTime = QDateTime::currentDateTime();
    data->logMsg = strLogInfo;
    data->logLevel = level;

    m_tableModel->addRowData(data);

    ui->tableView->scrollToBottom();
}
