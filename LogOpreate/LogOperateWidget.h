#ifndef LOGOPERATEWIDGET_H
#define LOGOPERATEWIDGET_H

#include <QWidget>
#include "LogOperateTableMode.h"

namespace Ui {
    class LogOperateWidget;
}

//日志展示
class LogOperateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogOperateWidget(QWidget *parent = nullptr);
    virtual ~LogOperateWidget(void);

private slots:
    void on_toolButton_clearAll_clicked();
    void on_toolButton_delete_clicked();

private:
    Ui::LogOperateWidget *ui;
    LogOperateTableMode *m_tableModel;
    int m_nCurrentClickedRow;

    Q_SLOT void OnTableClicked(const QModelIndex &index);
    Q_SLOT void OnAppendLogInfo(QString strLogInfo, LogOperateLevel level);
};

#endif // LOGOPERATEWIDGET_H
