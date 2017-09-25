#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mylrc_form.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QProcess>
#include <QTextStream>
#include <QBuffer>
#include <QImageReader>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    void resolve_picture();
    void resolve_text();
/*窗体拖动*/
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_play_pushButton_clicked();

    void change_bar_position();

    void on_bar_horizontalSlider_valueChanged(int value);

    void on_volume_horizontalSlider_valueChanged(int value);

    void on_close_pushButton_clicked();

    void on_shrink_pushButton_clicked();

    void on_vol_pushButton_clicked();

    void on_next_pushButton_clicked();

    void on_previous_pushButton_clicked();

    void updateIndex();

    void on_play_style_pushButton_clicked();
    void play_state_change();

    void on_listWidget_clicked(const QModelIndex &index);


    void on_music_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_search_pushButton_clicked();

    void on_lrc_pushButton_clicked();

    void on_pixmap_pushButton_clicked();

    void updataPicture_text();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *music_player;
    int play_state = 0; //0暂停 1播放 2停止
    QTime pos_time;
    QTime max_time;

    QString str_music_name;
    int m_music_name_Width;
    int m_curIndex;

    bool mouse_is_press;
    QPoint  mouse_move_len;

    MyLrc_Form myLrc;

    QFont font;
    QTimer *timer_pic;
    QMap<qint64,QString> music_lrc;
    qint64 old_previous=0;
    qint64 previous = 0;
    qint64 later    = 0;
    int half_textListW=0;
};

#endif // MAINWINDOW_H
