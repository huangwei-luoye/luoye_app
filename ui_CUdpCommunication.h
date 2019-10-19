/********************************************************************************
** Form generated from reading UI file 'CUdpCommunication.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUDPCOMMUNICATION_H
#define UI_CUDPCOMMUNICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CUdpCommunication
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_title;
    QTextEdit *textEdit_udpData;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_start;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_clearAll;
    QPushButton *pushButton_send;
    QPushButton *pushButton_connect;
    QProgressBar *progressBar;
    QWidget *widget_wave;

    void setupUi(QWidget *CUdpCommunication)
    {
        if (CUdpCommunication->objectName().isEmpty())
            CUdpCommunication->setObjectName(QStringLiteral("CUdpCommunication"));
        CUdpCommunication->resize(592, 402);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        CUdpCommunication->setFont(font);
        horizontalLayout = new QHBoxLayout(CUdpCommunication);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CUdpCommunication);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_title = new QLabel(widget);
        label_title->setObjectName(QStringLiteral("label_title"));

        verticalLayout_2->addWidget(label_title);

        textEdit_udpData = new QTextEdit(widget);
        textEdit_udpData->setObjectName(QStringLiteral("textEdit_udpData"));

        verticalLayout_2->addWidget(textEdit_udpData);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        pushButton_start = new QPushButton(widget_2);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));

        gridLayout->addWidget(pushButton_start, 3, 0, 1, 1);

        pushButton_stop = new QPushButton(widget_2);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));

        gridLayout->addWidget(pushButton_stop, 3, 3, 1, 1);

        pushButton_clearAll = new QPushButton(widget_2);
        pushButton_clearAll->setObjectName(QStringLiteral("pushButton_clearAll"));

        gridLayout->addWidget(pushButton_clearAll, 0, 3, 1, 1);

        pushButton_send = new QPushButton(widget_2);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));

        gridLayout->addWidget(pushButton_send, 0, 2, 1, 1);

        pushButton_connect = new QPushButton(widget_2);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));

        gridLayout->addWidget(pushButton_connect, 0, 0, 1, 1);

        progressBar = new QProgressBar(widget_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 3, 1, 1, 2);


        verticalLayout_2->addWidget(widget_2);

        widget_wave = new QWidget(widget);
        widget_wave->setObjectName(QStringLiteral("widget_wave"));

        verticalLayout_2->addWidget(widget_wave);


        horizontalLayout->addWidget(widget);


        retranslateUi(CUdpCommunication);

        QMetaObject::connectSlotsByName(CUdpCommunication);
    } // setupUi

    void retranslateUi(QWidget *CUdpCommunication)
    {
        CUdpCommunication->setWindowTitle(QApplication::translate("CUdpCommunication", "Form", Q_NULLPTR));
        label_title->setText(QApplication::translate("CUdpCommunication", "\345\217\221\351\200\201/\346\216\245\346\224\266\346\225\260\346\215\256\357\274\232", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("CUdpCommunication", "\345\274\200\345\247\213", Q_NULLPTR));
        pushButton_stop->setText(QApplication::translate("CUdpCommunication", "\345\201\234\346\255\242", Q_NULLPTR));
        pushButton_clearAll->setText(QApplication::translate("CUdpCommunication", "\346\270\205\347\251\272", Q_NULLPTR));
        pushButton_send->setText(QApplication::translate("CUdpCommunication", "\345\217\221\351\200\201", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("CUdpCommunication", "\350\277\236\346\216\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CUdpCommunication: public Ui_CUdpCommunication {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUDPCOMMUNICATION_H
