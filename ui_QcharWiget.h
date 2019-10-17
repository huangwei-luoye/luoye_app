/********************************************************************************
** Form generated from reading UI file 'QcharWiget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCHARWIGET_H
#define UI_QCHARWIGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QcharWiget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;

    void setupUi(QWidget *QcharWiget)
    {
        if (QcharWiget->objectName().isEmpty())
            QcharWiget->setObjectName(QString::fromUtf8("QcharWiget"));
        QcharWiget->resize(482, 300);
        horizontalLayout_2 = new QHBoxLayout(QcharWiget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        horizontalLayout_2->addLayout(gridLayout);


        retranslateUi(QcharWiget);

        QMetaObject::connectSlotsByName(QcharWiget);
    } // setupUi

    void retranslateUi(QWidget *QcharWiget)
    {
        QcharWiget->setWindowTitle(QApplication::translate("QcharWiget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QcharWiget: public Ui_QcharWiget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCHARWIGET_H
