/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_title;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_logo;
    QLabel *label_version;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_min;
    QPushButton *pushButton_close;
    QWidget *widget_udpCommunication;
    QWidget *widget_log;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(958, 663);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_title = new QWidget(centralWidget);
        widget_title->setObjectName(QStringLiteral("widget_title"));
        verticalLayout_2 = new QVBoxLayout(widget_title);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_logo = new QLabel(widget_title);
        label_logo->setObjectName(QStringLiteral("label_logo"));

        horizontalLayout->addWidget(label_logo);

        label_version = new QLabel(widget_title);
        label_version->setObjectName(QStringLiteral("label_version"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(13);
        label_version->setFont(font);

        horizontalLayout->addWidget(label_version);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_min = new QPushButton(widget_title);
        pushButton_min->setObjectName(QStringLiteral("pushButton_min"));

        horizontalLayout->addWidget(pushButton_min);

        pushButton_close = new QPushButton(widget_title);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));

        horizontalLayout->addWidget(pushButton_close);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(widget_title);

        widget_udpCommunication = new QWidget(centralWidget);
        widget_udpCommunication->setObjectName(QStringLiteral("widget_udpCommunication"));
        widget_udpCommunication->setEnabled(true);

        verticalLayout->addWidget(widget_udpCommunication);

        widget_log = new QWidget(centralWidget);
        widget_log->setObjectName(QStringLiteral("widget_log"));
        widget_log->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(widget_log);

        verticalLayout->setStretch(1, 5);
        verticalLayout->setStretch(2, 2);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        label_logo->setText(QString());
        label_version->setText(QApplication::translate("MainWindow", "TDS\346\265\213\350\257\225\345\267\245\345\205\267", Q_NULLPTR));
        pushButton_min->setText(QString());
        pushButton_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
