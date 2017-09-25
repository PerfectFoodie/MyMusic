#ifndef MYLRC_FORM_H
#define MYLRC_FORM_H

#include <QWidget>
#include <QMap>
#include <QFileInfo>
#include <QTextCodec>
#include <QTimer>
#include <QMediaPlayer>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>

namespace Ui {
class MyLrc_Form;
}

class MyLrc_Form : public QWidget
{
    Q_OBJECT

public:
    explicit MyLrc_Form(QWidget *parent = 0);
    ~MyLrc_Form();
    void init(QString now_play_music_baseName,
              QStringList music_file_lrc_list,
              QMediaPlayer *music_player);
    void resolve_lrc();

    /*窗体拖动*/
    protected:
        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseMoveEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent(QMouseEvent *event);

        void paintEvent(QPaintEvent  *ev);

private slots:
    void updateTime();

private:
    Ui::MyLrc_Form *ui;
    QString all_lrc;
    QMap<quint64, QString> music_lrc;
    QString m_now_play_music_baeseName;
    QStringList m_music_file_lrc_list;
    QMediaPlayer *m_music_player;
    QTimer *timer;

    bool mouse_is_press;
    QPoint  mouse_move_len;

    //歌词和歌词遮罩
    QFont font;
    QLinearGradient linear_gradient;
    QLinearGradient maskLinearGradient;
    qreal           lrcMaskWidth;
    //每次歌词遮罩增加的宽度
    qreal           lrcMaskWidthInterval;
    qreal           add_lrcMaskWidthInterval;
    int             count;
};


#endif // MYLRC_FORM_H
