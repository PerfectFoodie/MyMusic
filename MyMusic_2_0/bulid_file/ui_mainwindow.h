/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *search_lineEdit;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_8;
    QListWidget *listWidget;
    QSlider *bar_horizontalSlider;
    QLabel *pos_time_label;
    QLabel *char_label;
    QLabel *duration_label;
    QListWidget *music_listWidget;
    QSlider *volume_horizontalSlider;
    QLabel *music_name_label;
    QPushButton *previous_pushButton;
    QPushButton *play_pushButton;
    QPushButton *next_pushButton;
    QPushButton *lrc_pushButton;
    QPushButton *close_pushButton;
    QPushButton *shrink_pushButton;
    QLabel *Icon_label;
    QPushButton *search_pushButton;
    QPushButton *vol_pushButton;
    QLabel *show_musicname_label;
    QPushButton *play_style_pushButton;
    QPushButton *pixmap_pushButton;
    QLabel *pixmap_text_label;
    QLabel *pixmap_label;
    QListWidget *text_listWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1200, 1000);
        MainWindow->setAnimated(true);
        MainWindow->setDocumentMode(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        search_lineEdit = new QLineEdit(centralWidget);
        search_lineEdit->setObjectName(QStringLiteral("search_lineEdit"));
        search_lineEdit->setGeometry(QRect(210, 95, 161, 40));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 150, 800, 5));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(200, 0, 5, 650));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(200, 80, 800, 5));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(0, 0, 1000, 5));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(0, 0, 5, 650));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(1000, 0, 5, 650));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(0, 650, 1000, 5));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        line_8 = new QFrame(centralWidget);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(0, 550, 690, 5));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        listWidget = new QListWidget(centralWidget);
        QBrush brush(QColor(255, 85, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(13);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setFont(font);
        __qlistwidgetitem->setBackground(brush);
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(false);
        font1.setWeight(50);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setFont(font1);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(2, 152, 199, 435));
        bar_horizontalSlider = new QSlider(centralWidget);
        bar_horizontalSlider->setObjectName(QStringLiteral("bar_horizontalSlider"));
        bar_horizontalSlider->setEnabled(false);
        bar_horizontalSlider->setGeometry(QRect(469, 600, 421, 40));
        bar_horizontalSlider->setOrientation(Qt::Horizontal);
        bar_horizontalSlider->setTickPosition(QSlider::TicksBothSides);
        pos_time_label = new QLabel(centralWidget);
        pos_time_label->setObjectName(QStringLiteral("pos_time_label"));
        pos_time_label->setGeometry(QRect(900, 600, 40, 40));
        char_label = new QLabel(centralWidget);
        char_label->setObjectName(QStringLiteral("char_label"));
        char_label->setGeometry(QRect(940, 600, 10, 40));
        duration_label = new QLabel(centralWidget);
        duration_label->setObjectName(QStringLiteral("duration_label"));
        duration_label->setGeometry(QRect(950, 600, 40, 40));
        music_listWidget = new QListWidget(centralWidget);
        music_listWidget->setObjectName(QStringLiteral("music_listWidget"));
        music_listWidget->setGeometry(QRect(201, 152, 800, 435));
        volume_horizontalSlider = new QSlider(centralWidget);
        volume_horizontalSlider->setObjectName(QStringLiteral("volume_horizontalSlider"));
        volume_horizontalSlider->setGeometry(QRect(830, 95, 150, 40));
        volume_horizontalSlider->setValue(50);
        volume_horizontalSlider->setOrientation(Qt::Horizontal);
        volume_horizontalSlider->setTickPosition(QSlider::NoTicks);
        volume_horizontalSlider->setTickInterval(0);
        music_name_label = new QLabel(centralWidget);
        music_name_label->setObjectName(QStringLiteral("music_name_label"));
        music_name_label->setGeometry(QRect(250, 35, 580, 40));
        music_name_label->setStyleSheet(QStringLiteral("font: 75 14pt \"PMingLiU\";"));
        previous_pushButton = new QPushButton(centralWidget);
        previous_pushButton->setObjectName(QStringLiteral("previous_pushButton"));
        previous_pushButton->setGeometry(QRect(20, 600, 40, 40));
        previous_pushButton->setFlat(true);
        play_pushButton = new QPushButton(centralWidget);
        play_pushButton->setObjectName(QStringLiteral("play_pushButton"));
        play_pushButton->setGeometry(QRect(80, 600, 40, 40));
        play_pushButton->setFlat(true);
        next_pushButton = new QPushButton(centralWidget);
        next_pushButton->setObjectName(QStringLiteral("next_pushButton"));
        next_pushButton->setGeometry(QRect(140, 600, 40, 40));
        next_pushButton->setFlat(true);
        lrc_pushButton = new QPushButton(centralWidget);
        lrc_pushButton->setObjectName(QStringLiteral("lrc_pushButton"));
        lrc_pushButton->setGeometry(QRect(220, 600, 40, 40));
        lrc_pushButton->setStyleSheet(QStringLiteral(""));
        lrc_pushButton->setFlat(false);
        close_pushButton = new QPushButton(centralWidget);
        close_pushButton->setObjectName(QStringLiteral("close_pushButton"));
        close_pushButton->setGeometry(QRect(975, 0, 25, 25));
        close_pushButton->setFlat(false);
        shrink_pushButton = new QPushButton(centralWidget);
        shrink_pushButton->setObjectName(QStringLiteral("shrink_pushButton"));
        shrink_pushButton->setGeometry(QRect(940, 0, 25, 25));
        shrink_pushButton->setFlat(false);
        Icon_label = new QLabel(centralWidget);
        Icon_label->setObjectName(QStringLiteral("Icon_label"));
        Icon_label->setGeometry(QRect(60, 35, 80, 80));
        search_pushButton = new QPushButton(centralWidget);
        search_pushButton->setObjectName(QStringLiteral("search_pushButton"));
        search_pushButton->setGeometry(QRect(380, 95, 40, 40));
        search_pushButton->setFlat(false);
        vol_pushButton = new QPushButton(centralWidget);
        vol_pushButton->setObjectName(QStringLiteral("vol_pushButton"));
        vol_pushButton->setGeometry(QRect(780, 95, 40, 40));
        vol_pushButton->setFlat(false);
        show_musicname_label = new QLabel(centralWidget);
        show_musicname_label->setObjectName(QStringLiteral("show_musicname_label"));
        show_musicname_label->setGeometry(QRect(330, 605, 121, 30));
        play_style_pushButton = new QPushButton(centralWidget);
        play_style_pushButton->setObjectName(QStringLiteral("play_style_pushButton"));
        play_style_pushButton->setGeometry(QRect(720, 95, 40, 40));
        pixmap_pushButton = new QPushButton(centralWidget);
        pixmap_pushButton->setObjectName(QStringLiteral("pixmap_pushButton"));
        pixmap_pushButton->setGeometry(QRect(270, 600, 40, 40));
        pixmap_text_label = new QLabel(centralWidget);
        pixmap_text_label->setObjectName(QStringLiteral("pixmap_text_label"));
        pixmap_text_label->setGeometry(QRect(0, 35, 1000, 552));
        pixmap_label = new QLabel(centralWidget);
        pixmap_label->setObjectName(QStringLiteral("pixmap_label"));
        pixmap_label->setGeometry(QRect(120, 170, 300, 300));
        text_listWidget = new QListWidget(centralWidget);
        text_listWidget->setObjectName(QStringLiteral("text_listWidget"));
        text_listWidget->setGeometry(QRect(550, 99, 350, 451));
        MainWindow->setCentralWidget(centralWidget);
        search_lineEdit->raise();
        line->raise();
        line_2->raise();
        line_3->raise();
        line_4->raise();
        line_5->raise();
        line_6->raise();
        line_7->raise();
        line_8->raise();
        listWidget->raise();
        bar_horizontalSlider->raise();
        pos_time_label->raise();
        char_label->raise();
        duration_label->raise();
        music_listWidget->raise();
        volume_horizontalSlider->raise();
        music_name_label->raise();
        previous_pushButton->raise();
        play_pushButton->raise();
        next_pushButton->raise();
        lrc_pushButton->raise();
        close_pushButton->raise();
        shrink_pushButton->raise();
        search_pushButton->raise();
        vol_pushButton->raise();
        show_musicname_label->raise();
        play_style_pushButton->raise();
        pixmap_pushButton->raise();
        Icon_label->raise();
        pixmap_text_label->raise();
        pixmap_label->raise();
        text_listWidget->raise();
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(listWidget, bar_horizontalSlider);
        QWidget::setTabOrder(bar_horizontalSlider, music_listWidget);
        QWidget::setTabOrder(music_listWidget, search_lineEdit);
        QWidget::setTabOrder(search_lineEdit, volume_horizontalSlider);
        QWidget::setTabOrder(volume_horizontalSlider, previous_pushButton);
        QWidget::setTabOrder(previous_pushButton, play_pushButton);
        QWidget::setTabOrder(play_pushButton, next_pushButton);
        QWidget::setTabOrder(next_pushButton, lrc_pushButton);
        QWidget::setTabOrder(lrc_pushButton, close_pushButton);
        QWidget::setTabOrder(close_pushButton, shrink_pushButton);
        QWidget::setTabOrder(shrink_pushButton, search_pushButton);
        QWidget::setTabOrder(search_pushButton, vol_pushButton);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "\346\234\254\345\234\260\351\237\263\344\271\220", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "\351\237\263\344\271\220\346\226\207\344\273\266\345\244\271", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        pos_time_label->setText(QApplication::translate("MainWindow", "00:00", 0));
        char_label->setText(QApplication::translate("MainWindow", "/", 0));
        duration_label->setText(QApplication::translate("MainWindow", "00:00", 0));
        music_name_label->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        previous_pushButton->setText(QString());
        play_pushButton->setText(QString());
        next_pushButton->setText(QString());
        lrc_pushButton->setText(QApplication::translate("MainWindow", "\350\257\215", 0));
        close_pushButton->setText(QString());
        shrink_pushButton->setText(QString());
        Icon_label->setText(QString());
        search_pushButton->setText(QString());
        vol_pushButton->setText(QString());
        show_musicname_label->setText(QString());
        play_style_pushButton->setText(QApplication::translate("MainWindow", "\345\272\217", 0));
        pixmap_pushButton->setText(QApplication::translate("MainWindow", "\345\233\276", 0));
        pixmap_text_label->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", 0));
        pixmap_label->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt;\">\345\233\276</span></p></body></html>", 0));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
