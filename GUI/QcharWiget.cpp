#include "QcharWiget.h"
#include "ui_QcharWiget.h"
#include <QXYSeries>
#include <QValueAxis>
#include <QtCharts/QChartView>
#include <UtilityClasses/CQssFileAdaption.h>
#include <QGridLayout>
#include <QDebug>
#include <QMetaType>


QcharWiget::QcharWiget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QcharWiget)
{
    qRegisterMetaType<QList<QPointF>>("QList<QPointF>");

    ui->setupUi(this);
    QChartView *pchartView = new QChartView(CreateChart(TYPE_SPLINE));
    pchartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout->addWidget(pchartView);

    connect(this, SIGNAL(SourceWaveSignal(QByteArray)), &m_workThread, SLOT(OnSourceWave(QByteArray)));
    connect(&m_workThread, SIGNAL(ShowWaveSignal(QList<QPointF>)), this, SLOT(OnShowWave(QList<QPointF>)));
    connect(this, SIGNAL(CloseTimerSignal()), &m_workThread, SLOT(OnCloseTimer()));
}

QcharWiget::~QcharWiget()
{
    delete ui;
}

QcharWiget *QcharWiget::getInstance()
{
    static QcharWiget instance;
    return &instance;
}

QChart *QcharWiget::CreateChart(LINE_TYPE type)
{
    QChart *pchart = nullptr;

    switch(type)
    {
        case TYPE_SPLINE:
        {
            pchart = new QChart();
            pchart->setTitle(tr("实时采集波形"));
            pchart->legend()->hide();
            pchart->setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
            QValueAxis *asisX = new QValueAxis();
            QValueAxis *asisY = new QValueAxis();
            asisX->setRange(0, 500);
            asisY->setRange(-32767,32768);
            asisX->setTickCount(5+1);
            asisY->setTickCount(5+1);
            asisX->setTitleText("time");
            asisY->setTitleText("temp");
            asisX->setLabelFormat("%d");
            asisY->setLabelFormat("%.1f");

            m_pSeries = new QSplineSeries(pchart);
            m_pSeries->setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
            pchart->addSeries(m_pSeries);
            pchart->setAxisX(asisX,m_pSeries);
            pchart->setAxisY(asisY,m_pSeries);

        }break;
        case TYPE_LINE:
            break;
    }
    return pchart;
}

void QcharWiget::OnShowWave(QList<QPointF> data)
{
    //qDebug()<<"22-"<<this->thread()->currentThreadId();
    m_pSeries->replace(data);
}

void QcharWiget::OnWaveData(const QByteArray &data)
{
    emit SourceWaveSignal(data);
}

void QcharWiget::OnClosePaint()
{
    emit CloseTimerSignal();
}

