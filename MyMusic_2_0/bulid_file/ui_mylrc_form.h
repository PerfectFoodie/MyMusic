/********************************************************************************
** Form generated from reading UI file 'mylrc_form.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYLRC_FORM_H
#define UI_MYLRC_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyLrc_Form
{
public:
    QLabel *music_lrc_label;

    void setupUi(QWidget *MyLrc_Form)
    {
        if (MyLrc_Form->objectName().isEmpty())
            MyLrc_Form->setObjectName(QStringLiteral("MyLrc_Form"));
        MyLrc_Form->resize(800, 100);
        music_lrc_label = new QLabel(MyLrc_Form);
        music_lrc_label->setObjectName(QStringLiteral("music_lrc_label"));
        music_lrc_label->setGeometry(QRect(0, 0, 800, 100));

        retranslateUi(MyLrc_Form);

        QMetaObject::connectSlotsByName(MyLrc_Form);
    } // setupUi

    void retranslateUi(QWidget *MyLrc_Form)
    {
        MyLrc_Form->setWindowTitle(QApplication::translate("MyLrc_Form", "Form", 0));
        music_lrc_label->setText(QApplication::translate("MyLrc_Form", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt;\">\351\235\222\345\237\216\345\261\261\345\260\217\345\222\214\345\260\232\347\232\204\346\222\255\346\224\276\345\231\250</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MyLrc_Form: public Ui_MyLrc_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYLRC_FORM_H
