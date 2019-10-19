#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_min_clicked();

private:
    Ui::MainWindow *ui;
    void initUI();
    Q_SLOT void initNetwork();
    Q_SIGNAL void EnablePushButtonSignal();
};

#endif // MAINWINDOW_H
