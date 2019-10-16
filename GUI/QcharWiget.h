#ifndef QCHARWIGET_H
#define QCHARWIGET_H

#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QSplineSeries>
#include "ControlSercice/CWaveDataPraseThread.h"
#include <QChart>
#include <QTimer>
#include <QList>
#include <QPointF>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class QcharWiget;
}

typedef enum _LINE_TYPE
{
    TYPE_SPLINE,
    TYPE_LINE,
}LINE_TYPE;

class QcharWiget : public QWidget
{
    Q_OBJECT

public:
    explicit QcharWiget(QWidget *parent = nullptr);
    ~QcharWiget();

    static QcharWiget *getInstance();

private:
    Ui::QcharWiget *ui;

    QSplineSeries *m_pSeries;

    QChart *CreateChart(LINE_TYPE type);
    CWaveDataPraseThread m_workThread;

    Q_SLOT void OnShowWave(QList<QPointF> data);
    Q_SLOT void OnWaveData(const QByteArray &data);
    Q_SLOT void OnClosePaint();
    Q_SIGNAL void SourceWaveSignal(const QByteArray &srcData);
    Q_SIGNAL void CloseTimerSignal();

};

#endif // QCHARWIGET_H
