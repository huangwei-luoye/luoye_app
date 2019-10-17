/********************************************************************************
** Form generated from reading UI file 'LogOperateWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGOPERATEWIDGET_H
#define UI_LOGOPERATEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogOperateWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_icon;
    QLabel *label_title;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_clearAll;
    QToolButton *toolButton_delete;
    QTableView *tableView;

    void setupUi(QWidget *LogOperateWidget)
    {
        if (LogOperateWidget->objectName().isEmpty())
            LogOperateWidget->setObjectName(QString::fromUtf8("LogOperateWidget"));
        LogOperateWidget->resize(624, 288);
        verticalLayout = new QVBoxLayout(LogOperateWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(LogOperateWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 25));
        widget->setMaximumSize(QSize(16777215, 25));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(231, 231, 231, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        widget->setPalette(palette);
        widget->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 10, 0);
        label_icon = new QLabel(widget);
        label_icon->setObjectName(QString::fromUtf8("label_icon"));

        horizontalLayout->addWidget(label_icon);

        label_title = new QLabel(widget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setStyleSheet(QString::fromUtf8("border-image:url();\n"
"background-color: rgb();"));

        horizontalLayout->addWidget(label_title);

        horizontalSpacer = new QSpacerItem(341, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton_clearAll = new QToolButton(widget);
        toolButton_clearAll->setObjectName(QString::fromUtf8("toolButton_clearAll"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolButton_clearAll->sizePolicy().hasHeightForWidth());
        toolButton_clearAll->setSizePolicy(sizePolicy1);
        toolButton_clearAll->setMinimumSize(QSize(60, 25));
        toolButton_clearAll->setStyleSheet(QString::fromUtf8("border-image:url();\n"
"background-color: rgb();"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/bin/res/imgs/img_main/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_clearAll->setIcon(icon);
        toolButton_clearAll->setIconSize(QSize(20, 20));
        toolButton_clearAll->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_clearAll->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_clearAll);

        toolButton_delete = new QToolButton(widget);
        toolButton_delete->setObjectName(QString::fromUtf8("toolButton_delete"));
        toolButton_delete->setMinimumSize(QSize(60, 25));
        toolButton_delete->setStyleSheet(QString::fromUtf8("border-image:url();\n"
"background-color: rgb();"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/bin/res/imgs/img_main/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_delete->setIcon(icon1);
        toolButton_delete->setIconSize(QSize(20, 20));
        toolButton_delete->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_delete->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_delete);


        verticalLayout->addWidget(widget);

        tableView = new QTableView(LogOperateWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(LogOperateWidget);

        QMetaObject::connectSlotsByName(LogOperateWidget);
    } // setupUi

    void retranslateUi(QWidget *LogOperateWidget)
    {
        LogOperateWidget->setWindowTitle(QApplication::translate("LogOperateWidget", "LogOperateWidget", nullptr));
        label_icon->setText(QString());
        label_title->setText(QApplication::translate("LogOperateWidget", "  \347\263\273\347\273\237\346\227\245\345\277\227  ", nullptr));
        toolButton_clearAll->setText(QApplication::translate("LogOperateWidget", "\346\270\205\347\251\272", nullptr));
        toolButton_delete->setText(QApplication::translate("LogOperateWidget", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogOperateWidget: public Ui_LogOperateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGOPERATEWIDGET_H
