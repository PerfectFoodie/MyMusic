#include "header.h"
#include "mylrc_form.h"
#include "ui_mylrc_form.h"
#include <QDebug>


MyLrc_Form::MyLrc_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyLrc_Form)
{
    ui->setupUi(this);

    //ui->music_lrc_label->setStyleSheet("background:transparent");
    setStyleSheet("QLabel{background: rgb(50,50,50,50);border: 1px solid gray;}");
    //ui->music_lrc_label->setAttribute(Qt::WA_TranslucentBackground);


    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint|Qt::Tool|Qt::X11BypassWindowManagerHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowOpacity(0.7);
    // 设置字体
    font.setFamily("Times New Roman");
    font.setBold(true);
    font.setPointSize(30);
    ui->music_lrc_label->setFont(font);

    //歌词的线性渐变填充
    linear_gradient.setStart(0, 10);//填充的起点坐标
    linear_gradient.setFinalStop(0, 40);//填充的终点坐标
    //第一个参数终点坐标，相对于我们上面的区域而言，按照比例进行计算
    linear_gradient.setColorAt(0.1, QColor(14, 179, 255));
    linear_gradient.setColorAt(0.5, QColor(114, 232, 255));
    linear_gradient.setColorAt(0.9, QColor(14, 179, 255));

    //遮罩线性渐变填充
    maskLinearGradient.setStart(0, 10);
    maskLinearGradient.setFinalStop(0, 40);
    maskLinearGradient.setColorAt(0.1, QColor(222,54,4));
    maskLinearGradient.setColorAt(0.5, QColor(255,72,16));
    maskLinearGradient.setColorAt(0.9, QColor(222,54,4));


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(50);
    ui->music_lrc_label->setAlignment(Qt::AlignCenter);

    //隐藏label
    ui->music_lrc_label->hide();

}

MyLrc_Form::~MyLrc_Form()
{
    delete ui;
}

void MyLrc_Form::init(QString now_play_music_baseName,
                      QStringList music_file_lrc_list,
                      QMediaPlayer *music_player)
{
    all_lrc.clear();
    music_lrc.clear();
    m_now_play_music_baeseName = now_play_music_baseName;
    m_music_file_lrc_list = music_file_lrc_list;
    m_music_player = music_player;
    for (int i=0; i<m_music_file_lrc_list.count(); i++)
    {
        QFileInfo lrc_file_info(m_music_file_lrc_list.at(i));
        if (m_now_play_music_baeseName != lrc_file_info.baseName())
            continue ;
        QFile lrc_file(m_music_file_lrc_list.at(i));
        if (!lrc_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ui->music_lrc_label->setText("打开 "+m_now_play_music_baeseName+" 歌词文件失败");
            return ;
        }
        //*******这种方式读取中文没有乱码
        QTextStream in(&lrc_file);
        all_lrc=in.readAll();
        lrc_file.close();
        //歌词解析
        resolve_lrc();
        return ;
    }
    qDebug() <<"未找到歌词文件";
    /*未找到音乐歌词文件*/
    ui->music_lrc_label->setText("未找到 "+m_now_play_music_baeseName+" 歌词文件");
}
/*歌词解析*/
void MyLrc_Form::resolve_lrc()
{
    //将歌词按行分解为歌词列表
    QStringList lines = all_lrc.split("\n");
//    QStringList lines;
//    qDebug() <<all_lrc;
//    qDebug() <<lines;
    //使用正则表达式将时间标签和歌词内容分离
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach (QString oneLine, lines)
    {
        //先在当前行的歌词的备份中将时间内容清除，得到歌词文本
        QString temp = oneLine;
        temp.replace(rx, "");
        qDebug()<< oneLine;
        //然后依次获得当前行中所有的时间标签，并分别与歌词文本存入QMap
        int pos = 0;
            pos = rx.indexIn(oneLine, pos);
        qDebug() <<pos << "==================================";
        while (pos != -1)
        {
            QString cap = rx.cap(0);
            //将时间标签转换为时间数值，以毫秒为单位
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            qint64 totalTime = minute*60000 + second*1000 + millisecond*10;
            qDebug() <<totalTime;
            //插入到music_lrc
            music_lrc.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneLine, pos);
            qDebug() <<music_lrc;
        }
    }
    //如果music_lrc为空
    if (music_lrc.isEmpty())
    {
        ui->music_lrc_label->setText("歌词解析错误");
        return ;
    }
//    else
//    {
//        ui->music_lrc_label->setText(music_lrc.first());
//    }
}

void MyLrc_Form::updateTime()
{
    if ( music_lrc.isEmpty())
    {
        qDebug() << "updateTime(): music_lrc is empty";
        return ;
    }
    //获取当前时间在歌词中的前后两个时间点
    qint64 old_previous=0;
    qint64 previous = 0;
    qint64 later    = 0;
    foreach (qint64 value, music_lrc.keys())
    {
        if ( m_music_player->position() >= value )
        {
            if (old_previous==0)
                old_previous = 1;
            else
                old_previous = previous;

            previous = value;

        }
        else
        {
            later = value;
            break ;
        }
    }
    //达到最后一行，将later设置为歌曲总时间的值
    if (later == 0)
        later =  m_music_player->duration();
    //获取当前时间所对应的歌词内容
    QString currentLrc = music_lrc.value(previous);


    //新的一行歌词，重新开始显示歌词
    if (currentLrc != ui->music_lrc_label->text())
    {
        qDebug() << "  zong time: " << (later-previous);

       ui->music_lrc_label->setText(currentLrc);
       if (ui->music_lrc_label->text() == "")
           {
                ui->music_lrc_label->setText(music_lrc.value(old_previous));
                return ;
           }

       count = (later-previous)/50;
       qDebug() << "count : " << count;
       //lrcMaskWidth = (qreal)ui->music_lrc_label->text().length();
       lrcMaskWidth = ui->music_lrc_label->width() + 200;
       //lrcMaskWidth = 800 - (qreal)ui->music_lrc_label->font().wordSpacing();
       qDebug() <<"lrc: " << lrcMaskWidth;
       lrcMaskWidthInterval = ((lrcMaskWidth)/count);
       qDebug() <<"lrcinterval: "<<lrcMaskWidthInterval;
       add_lrcMaskWidthInterval = lrcMaskWidthInterval;
    }
    else
    {
       this->update();
    }

}


/*窗体拖动*/
//重写鼠标按下事件
void MyLrc_Form::mousePressEvent(QMouseEvent *event)
{
    mouse_is_press = true;
    mouse_move_len = event->globalPos() - this->pos();
}
//重写鼠标移动事件
void MyLrc_Form::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)按下是左键
    //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (  mouse_is_press && (event->buttons() && Qt::LeftButton) &&
          (event->globalPos()-mouse_move_len).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos() - mouse_move_len);
        mouse_move_len = event->globalPos() - pos();
    }
}
//重写鼠标释放事件
void MyLrc_Form::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_is_press = false;
}

void MyLrc_Form::paintEvent(QPaintEvent  *ev)
{
    qDebug() <<"1111111111111111111111111111111111111111111111111";
    qDebug() << count ;
    qDebug() << lrcMaskWidth;
    qDebug() << lrcMaskWidthInterval;
    qDebug() << add_lrcMaskWidthInterval;

    QPainter painter(this);
    painter.setFont(font);

    if (music_lrc.isEmpty())
    {
       ui->music_lrc_label->show();
       return ;
    }
    else
    {
        ui->music_lrc_label->hide();
    }

    painter.setPen(QPen(linear_gradient, 0));
    painter.drawText(0,0,
                     800,100,Qt::AlignVCenter,ui->music_lrc_label->text());

    //font.setPointSize(35);
   // painter.setFont(font);
    painter.setPen(QPen(maskLinearGradient, 0));
    painter.drawText(0,0,
                     lrcMaskWidthInterval,100,Qt::AlignVCenter ,ui->music_lrc_label->text());
    lrcMaskWidthInterval = lrcMaskWidthInterval + add_lrcMaskWidthInterval;


    qDebug() << "label---------------------------- " << ui->music_lrc_label->x() << ui->music_lrc_label->y() ;
    qDebug() << "this----------------------------- " << this->x() << this->y();
}




