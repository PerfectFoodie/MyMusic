#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "header.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    music_player = new QMediaPlayer(this);

    init();
    connect(music_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(play_state_change()));
}

void MainWindow::updateIndex()
{
    qDebug() << "updata" ;
    if (str_music_name == NULL)
    {
        return ;
    }
    ui->show_musicname_label->setText(str_music_name.mid(m_curIndex) + "   " +str_music_name.left(m_curIndex));
    m_curIndex++;
    if (m_curIndex >= m_music_name_Width+1)
        m_curIndex = 0;
}


/*窗体拖动*/
//重写鼠标按下事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mouse_is_press = true;
    mouse_move_len = event->globalPos() - pos();
}
//重写鼠标移动事件
void MainWindow::mouseMoveEvent(QMouseEvent *event)
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
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_is_press = false;
}


MainWindow::~MainWindow()
{
    delete ui;
}

/* 初始化 */
void MainWindow::init()
{
    /*图标*/
    QPixmap pixmap(":/images/Icon.jpg");
    pixmap = pixmap.scaled(ui->Icon_label->width(), ui->Icon_label->height(),
    Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和
    ui->Icon_label->setPixmap(pixmap);
    ui->close_pushButton->setIcon(QIcon(":/images/close.png"));
    ui->listWidget->item(0)->setIcon(QIcon(":/images/mymusic.png"));
    ui->listWidget->item(0)->setTextAlignment(Qt::AlignHCenter);
    ui->listWidget->item(1)->setIcon(QIcon(":/images/music_file.png"));
    ui->listWidget->item(1)->setTextAlignment(Qt::AlignHCenter);
    ui->shrink_pushButton->setIcon(QIcon(":/images/shrink.png"));

    ui->previous_pushButton->setIcon(QIcon(":/images/previous_song1.png"));
    ui->play_pushButton->setIcon(QIcon(":/images/play.png"));
    ui->next_pushButton->setIcon(QIcon(":/images/next_song.png"));
    ui->search_pushButton->setIcon(QIcon(":/images/search.png"));
    ui->vol_pushButton->setIcon(QIcon(":/images/sound.png"));
    ui->music_name_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    myLrc.setFixedSize(800, 100);
    //myLrc.setGeometry(550,925,800,100);
    //myLrc.show();
    ui->lrc_pushButton->setText(tr("关"));
    ui->pixmap_text_label->hide();
    ui->pixmap_label->hide();
    ui->text_listWidget->hide();
    ui->pixmap_pushButton->setText("图");
    ui->text_listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->text_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->text_listWidget->setStyleSheet("padding: 20px;");



    /*音乐文件夹路径是否存在*/
    QDir music_dir;
    music_dir.setPath("./../music");
    if (!music_dir.exists())
    {
        QMessageBox::information(this, tr("information"),
                                tr("the dir 'music' is not exist"), QMessageBox::Ok);
        exit(0);
    }
    /*是否有音乐文件,音乐歌词文件*/
    music_dir.setFilter(QDir::Files);
    QFileInfoList list = music_dir.entryInfoList();
    if (list.count() <= 0)
    {
        QMessageBox::information(this, tr("inmformation"),
                                 tr("not have music"), QMessageBox::Ok);
        return ;
    }
    /*过滤音乐文件*/
    for (int i=0; i<list.count(); i++)
    {
        QFileInfo file_info = list.at(i);
        QString   suffix    = file_info.suffix();
        if (QString::compare(suffix, QString("mp3"), Qt::CaseInsensitive) == 0)
        {
            music_file_path_list.append(file_info.absoluteFilePath());
            continue ;
        }
        //歌词文件
        if (QString::compare(suffix, QString("lrc"), Qt::CaseInsensitive) == 0)
            music_file_lrc_list.append(file_info.absoluteFilePath());
        //歌词图片
        if (QString::compare(suffix, QString("jpg"), Qt::CaseInsensitive) == 0)
            music_file_picture.append(file_info.absoluteFilePath());

    }

    /*将文件添加到本地音乐中*/
    for (int j=0; j<music_file_path_list.count(); j++)
    {
        QFileInfo music_info(music_file_path_list.at(j));
        music_file_name_list.append(music_info.baseName());
    }
    ui->music_listWidget->addItems(music_file_name_list);
    /*设置item行高*/
    for (int m=0; m<ui->music_listWidget->count(); m++)
    {
        ui->music_listWidget->item(m)->setSizeHint(QSize(50, 50));
    }

    m_curIndex = 0;//当前角码

}

/*播放*/
void MainWindow::on_play_pushButton_clicked()
{
    //if (music_player->state() == QMediaPlayer::PlayingState) //此时为播放状态
    if (play_state ==1)
    {
         play_state = 0;
         music_player->pause();
        ui->play_pushButton->setIcon(QIcon(":/images/play.png"));
        return ;
    }

    if (music_player->isAudioAvailable() && play_state == 0)
    {
        if (ui->music_name_label->text() == ui->music_listWidget->currentItem()->text())
        {
            qDebug() << "on_play_pushButton_clicked: state:1";
            play_state = 1;
            music_player->play();           
            ui->play_pushButton->setIcon(QIcon(":/images/pause.png"));
            return ;
        }
    }
    if (ui->music_listWidget->currentItem() == NULL)
    {
        QMessageBox::information(this, tr("information"), tr("not choice music"), QMessageBox::Ok);
        return ;
    }

    QListWidgetItem *current_item = ui->music_listWidget->currentItem();
    for (int i=0; i<music_file_path_list.count(); i++)
    {
        QFileInfo file_info(music_file_path_list.at(i));
        if (file_info.baseName() != current_item->text())
            continue;
        if (file_info.baseName() == current_item->text())
        {
            music_player->setMedia(QUrl(music_file_path_list.at(i)));
            ui->music_name_label->setText(file_info.baseName());   //显示歌曲名
            str_music_name = file_info.baseName();
            m_music_name_Width = file_info.baseName().length();
            ui->music_name_label->setAlignment(Qt::AlignHCenter);  //文字居中显示
            /*转换为暂停键*/
            ui->play_pushButton->setIcon(QIcon(":/images/pause.png"));
            /*初始化滑动条*/
            ui->bar_horizontalSlider->setEnabled(true);
            connect(music_player, SIGNAL(positionChanged(qint64)), this, SLOT(change_bar_position()));
            pos_time.setHMS(0, 0, 0);
            ui->pos_time_label->setText(pos_time.toString("mm:ss"));
            ui->bar_horizontalSlider->setValue(0);

            QString music_name_play_now = file_info.baseName();
            qDebug() <<music_file_lrc_list;
            qDebug() <<music_file_name_list.count();
            qDebug() <<music_file_path_list.count();
            myLrc.init(music_name_play_now,
                        music_file_lrc_list,
                        music_player);
            myLrc.setFixedSize(800, 100);
            //myLrc.setGeometry(550,925,800,100);
            myLrc.show();
            ui->lrc_pushButton->setText(tr("关"));
            resolve_picture();
            resolve_text();
            play_state = 1;
            music_player->play();
            music_player->setVolume(ui->volume_horizontalSlider->value());

            return ;
        }
    }

    QMessageBox::information(this, tr("error"), tr("on_play_pushButton_clicked"), QMessageBox::Ok);
}
/* 音量 */
void MainWindow::on_volume_horizontalSlider_valueChanged(int value)
{
    music_player->setVolume(value);
    ui->vol_pushButton->setIcon(QIcon(":/images/sound.png"));
}
/* 随音乐播放,改变进度条位置 */
void MainWindow::change_bar_position()
{
    qDebug() << " ";
    qDebug() << "change_bar_position";

    if (play_state == 2)
    {
        qDebug() <<"stat==2";
        return ;
    }
    updateIndex();
    if (music_player->duration() != ui->bar_horizontalSlider->maximum())
    {
        qDebug() << "setmaximum";
        ui->bar_horizontalSlider->setMaximum(music_player->duration());
        max_time.setHMS(0, music_player->duration()/60000,
                          qRound((music_player->duration()%60000)/1000.0));
        ui->duration_label->setText(max_time.toString("mm:ss"));
        return ;
    }
    if(music_player->duration() == 0)
    {
       return ;
    }
    /*播放时间*/
    quint64  current_position = music_player->position();
    ui->bar_horizontalSlider->setValue(current_position);
    pos_time.setHMS(0, current_position/60000,
                      qRound((current_position%60000)/1000.0));
    ui->pos_time_label->setText(pos_time.toString("mm:ss"));

    qDebug() << "pos: " << pos_time << "   max: " << max_time;
    /*播放到尾*/
    //if(music_player->position() == (music_player->duration()) && play_state==1)
    if (music_player->position() >= ui->bar_horizontalSlider->maximum()-5 ||
            pos_time.addSecs(2) == max_time )
    //if (pos_time == max_time && music_player->state() == QMediaPlayer::PlayingState)
    {
       // if( music_player->state() == QMediaPlayer::StoppedState)
        qDebug() << "Stop";
        play_state = 2;
        music_player->stop();
        ui->play_pushButton->setIcon(QIcon(":/images/pause.png"));
        ui->bar_horizontalSlider->setValue(0);
        pos_time.setHMS(0, 0, 0);
        ui->pos_time_label->setText(pos_time.toString("mm:ss"));
    }
}
/* 进度条改变, 只关注人为拖动 */
void MainWindow::on_bar_horizontalSlider_valueChanged(int value)
{
    quint64 position = music_player->position();
    if( qAbs(value - position)>3000 && (value != 0))
    {
        music_player->setPosition(value);
        play_state = 1;
        music_player->play();      
        ui->play_pushButton->setIcon(QIcon(":/images/pause.png"));
    }
}
/* 关闭程序 */
void MainWindow::on_close_pushButton_clicked()
{
    exit(0);
}
/* 最小化窗口 */
void MainWindow::on_shrink_pushButton_clicked()
{
    this->showMinimized();
}
/* 开启静音 */
void MainWindow::on_vol_pushButton_clicked()
{
    ui->volume_horizontalSlider->setValue(0);
    ui->vol_pushButton->setIcon(QIcon(":/images/sound_close.png"));
}
/* 下一曲 */
void MainWindow::on_next_pushButton_clicked()
{
    qDebug() <<"on_next_pushButton_clicked";
    //if (music_player->state() ==  QMediaPlayer::PlayingState)
    if (play_state == 1)
    {
        qDebug() <<"play_stat ==0";
        play_state = 0;
        music_player->pause();       
        ui->play_pushButton->setIcon(QIcon(":/images/play.png"));
    }
    int current_row = ui->music_listWidget->currentRow();
    if (music_file_name_list.count() < current_row+2)
    {
        qDebug() <<"m1";
        ui->music_listWidget->setCurrentItem(ui->music_listWidget->item(0));
        on_play_pushButton_clicked();
        return ;
    }
    qDebug() <<"m2";
    /* 下一曲 */
    ui->music_listWidget->setCurrentItem(ui->music_listWidget->item(current_row+1));
    on_play_pushButton_clicked();

}
/* 上一曲 */
void MainWindow::on_previous_pushButton_clicked()
{
    //if (music_player->state() == QMediaPlayer::PlayingState)
    if(play_state == 1)
    {
        music_player->pause();
        play_state = 0;
        ui->play_pushButton->setIcon(QIcon(":/images/play.png"));
    }
    int current_row = ui->music_listWidget->currentRow();
    if (current_row == 0)
    {
        ui->music_listWidget->setCurrentItem(ui->music_listWidget->item(music_file_name_list.count()-1));
        on_play_pushButton_clicked();
        return ;
    }
    /* 上一曲 */
    ui->music_listWidget->setCurrentItem(ui->music_listWidget->item(current_row-1));
    on_play_pushButton_clicked();
}
/*播放顺序*/
void MainWindow::on_play_style_pushButton_clicked()
{
    qDebug() <<"on_play_style_pushButton_clicked";
    if (ui->play_style_pushButton->text() == "序")
    {
       on_next_pushButton_clicked();
    }
}
/* 播放器状态改变 */
void MainWindow::play_state_change()
{
    qDebug() << "play_state_change";
    //if (music_player->state() == QMediaPlayer::PlayingState)
    if (play_state == 1)
    {
        qDebug () << "play_state_change : state == 1";
        return ;
    }
    //if(music_player->state() == QMediaPlayer::PausedState)
    if (play_state == 0)
    {
        qDebug () << "play_state_change : state == 0";
        return ;
    }
    if (play_state == 2)
    {
        qDebug() << music_player->state() ;
        qDebug () << "play_state_change : state == 2";
        on_play_style_pushButton_clicked();
    }
}
/* 点击本地音乐item */
void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    if (index.row() == 0) //本地音乐
    {
        init();
        return ;
    }

    if (index.row() == 1) //音乐文件夹
    {
        QString path=QDir::currentPath();//获取程序当前目录
        path.replace("/","\\");//将地址中的"/"替换为"\"，因为在Windows下使用的是"\"。
        QString path_temp = path.left(path.indexOf("bulid_file"));
        path_temp.append("music");
        QProcess::startDetached("explorer " + path_temp);
        return ;
    }

}
/* 双击选择音乐 */
void MainWindow::on_music_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (music_player->state() == QMediaPlayer::PlayingState)
    {
        play_state = 0;
        music_player->pause();
        ui->play_pushButton->setIcon(QIcon(":/images/play.png"));
        qDebug() << music_player->state();
    }
    for (int i=0; i<music_file_path_list.count(); i++)
    {
        QFileInfo file_info(music_file_path_list.at(i));
        if (file_info.baseName() != item->text())
            continue;
        if (file_info.baseName() == item->text())
        {
            music_player->setMedia(QUrl(music_file_path_list.at(i)));
            ui->music_name_label->setText(file_info.baseName());   //显示歌曲名
            str_music_name = file_info.baseName();
            m_music_name_Width = file_info.baseName().length();
            ui->music_name_label->setAlignment(Qt::AlignHCenter);  //文字居中显示
            /*转换为暂停键*/
            ui->play_pushButton->setIcon(QIcon(":/images/pause.png"));
            /*初始化滑动条*/
            ui->bar_horizontalSlider->setEnabled(true);
            connect(music_player, SIGNAL(positionChanged(qint64)), this, SLOT(change_bar_position()));

            QString music_name_play_now = file_info.baseName();
            qDebug() <<music_file_lrc_list.count();
            qDebug() <<music_file_name_list.count();
            qDebug() <<music_file_path_list.count();
            myLrc.init(music_name_play_now,
                        music_file_lrc_list,
                        music_player);
            myLrc.setFixedSize(800, 100);
            //myLrc.setGeometry(550,925,800,100);
            myLrc.show();
            ui->lrc_pushButton->setText(tr("关"));
            resolve_picture();
            resolve_text();
            play_state = 1;
            music_player->play();
            music_player->setVolume(ui->volume_horizontalSlider->value());
            return ;
        }
    }
}
/* 搜索按钮 */
void MainWindow::on_search_pushButton_clicked()
{
    if (ui->search_lineEdit->text() == NULL)
    {
        return ;
    }
    QString str_sreach_text = ui->search_lineEdit->text();
    int count = ui->music_listWidget->count();
    for (int row=0; row<count; row++)
    {
        if (ui->music_listWidget->item(row)->text() != str_sreach_text)
            continue ;
        ui->music_listWidget->setCurrentItem(ui->music_listWidget->item(row));
    }

}
/* 显示歌词 */
void MainWindow::on_lrc_pushButton_clicked()
{
    if (ui->lrc_pushButton->text() == "词")
    {
        myLrc.setFixedSize(800, 100);
       // myLrc.setGeometry(550,925,800,100);
        myLrc.show();
        ui->lrc_pushButton->setText("关");
        return ;
    }
    if (ui->lrc_pushButton->text() == "关")
    {
        myLrc.hide();
        ui->lrc_pushButton->setText("词");
        return ;
    }
}
/* 图像文字 */
void MainWindow::on_pixmap_pushButton_clicked()
{
    if (ui->pixmap_pushButton->text() == "图")
    {
        //显示图文
        resolve_picture();
        resolve_text();
        ui->pixmap_text_label->show();
        ui->pixmap_label->show();
        ui->text_listWidget->show();
        ui->pixmap_pushButton->setText(tr("收"));
        return ;
    }
    if (ui->pixmap_pushButton->text() == "收")
    {
        //关闭图文

        ui->pixmap_text_label->hide();
        ui->pixmap_label->hide();
        ui->text_listWidget->hide();
        ui->pixmap_pushButton->setText("图");
        return ;
    }
}
/* 专辑图片 */
void MainWindow::resolve_picture()
{

    qDebug() << "resolve_picture()";
    ui->pixmap_label->clear();
    for (int i=0; i<music_file_picture.count(); i++)
    {
        QFileInfo music_file_info(music_file_picture.at(i));                  
        if (music_file_info.baseName() != ui->music_name_label->text())
            continue ;
        QPixmap pixmap(music_file_picture.at(i));
        pixmap = pixmap.scaled(ui->pixmap_label->width(), ui->pixmap_label->height(),
                        Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致
        ui->pixmap_label->setPixmap(pixmap);
        return ;
    }
       //默认图片
    QPixmap pixmap(":/images/Icon.jpg");
    pixmap = pixmap.scaled(ui->pixmap_label->width(), ui->pixmap_label->height(),
                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致
    ui->pixmap_label->setPixmap(pixmap);
}
/* 图文的歌词显示 */
void MainWindow::resolve_text()
{
     music_lrc.clear();
     half_textListW = 0;
     ui->text_listWidget->clear();
    /*设置歌词*/
    for (int j=0; j<music_file_lrc_list.count(); j++)
    {
        QFileInfo lrc_file_info(music_file_lrc_list.at(j));
        if (ui->music_name_label->text()!= lrc_file_info.baseName())
            continue ;
        QFile lrc_file(music_file_lrc_list.at(j));
        if (!lrc_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ui->text_listWidget->addItem(new QListWidgetItem(tr("歌词文件打开失败")));
            return ;
         }
         //*******这种方式读取中文没有乱码
         QTextStream in(&lrc_file);
         QString all_lrc=in.readAll();
         lrc_file.close();
         //放入歌词
         QStringList lrc_list = all_lrc.split("\n");
         QStringList lrc_list_str;
         QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
         foreach (QString oneLine, lrc_list)
         {
             //先在当前行的歌词的备份中将时间内容清除，得到歌词文本
             QString temp = oneLine;
             temp.replace(rx, "");
             qDebug() <<temp;
             if (temp=="")
                 continue ;

             //保存歌曲时间
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
                 lrc_list_str.append(temp);
             }
         }
         ui->text_listWidget->addItems(lrc_list_str);
         for (int m=0; m<ui->text_listWidget->count(); m++)
         {
              font.setFamily("Times New Roman");
              font.setBold(true);
              font.setPointSize(10);
              ui->text_listWidget->item(m)->setTextAlignment(Qt::AlignCenter);
              ui->text_listWidget->item(m)->setSizeHint(QSize(30,30));
              ui->text_listWidget->item(m)->setFont(font);
         }


         old_previous=0;
         previous = 0;
         later    = 0;
         updataPicture_text();
         timer_pic = new QTimer(this);
         connect(timer_pic, SIGNAL(timeout()), this, SLOT(updataPicture_text()));
         timer_pic->start(100);
    }
    ui->text_listWidget->addItem(new QListWidgetItem(tr("未找到歌词")));
}
/* 根据时间设置当前item */
void MainWindow::updataPicture_text()
{
    //根据时间设置当前item
    if ( music_lrc.isEmpty())
    {
        qDebug() << "updateTime(): music_lrc is empty";
        return ;
    }
    qDebug() <<"music_lrc is not Empty";
    //获取当前时间在歌词中的前后两个时间点
    foreach (qint64 value, music_lrc.keys())
    {
        if ( music_player->position() >= value )
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
        later =  music_player->duration();
    //获取当前时间所对应的歌词内容
    QString currentLrc = music_lrc.value(previous);
    qDebug() <<" currentLrc: " << currentLrc;
    for (int m=0; m<ui->text_listWidget->count(); m++)
    {
        if (ui->text_listWidget->item(m)->text() != currentLrc)
            continue ;
        ui->text_listWidget->setCurrentItem(ui->text_listWidget->item(m));

        break ;
    }

    //歌词到中间后保持位置
//    qDebug() <<"999999999999999999999999999999999999999999999999999999999999999999999999999999999999";
//    qDebug() << ui->text_listWidget->height() ;
//    qDebug() << ui->text_listWidget->currentRow() * 40;
//    if ( ui->text_listWidget->currentItem()->text() == "1")
//            return ;
//    if ( half_textListW > 250  )
//    {
//        ui->text_listWidget->takeItem(0);
//        half_textListW = half_textListW - 30;
//    }


}

//    qDebug() <<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
//    for (int i=0; i<music_file_path_list.count(); i++)
//    {
//        QFileInfo music_file_info(music_file_path_list.at(i));
//        if (music_file_info.baseName() != ui->music_name_label->text())
//            continue ;

//        QFile music_file(music_file_path_list.at(i));
//        if(!music_file.open(QIODevice::ReadOnly))
//        {
//            ui->pixmap_text_label->setText(tr("图片文件打开失败"));
//            return ;
//        }
//        //QString str_temp = music_file.readAll();
//        QString str;
//        QTextStream in(&music_file);
//        str = in.readAll();

//        if(str.indexOf("image/jpeg") != 0)
//        {
//            qDebug() <<"image/jpeg";
//        }

//        QString head = str.mid(str.indexOf("ID3"), 3);
//        if (head == "ID3")
//        {
//            qDebug() <<"ID3";
//        }
//        QString header = str.mid(0,10);
//        int size_all = header.at(6).toLatin1() * 0x200000  //获取该标签的尺寸，不包括标签头
//                + header.at(7).toLatin1() * 0x4000
//                + header.at(8).toLatin1() * 0x20
//                + header.at(9).toLatin1();
//        qDebug() << size_all;


//        qDebug() <<"file: " << music_file_info.baseName() << music_file_info.absoluteFilePath();
//        qDebug() <<"str: "<<str <<endl;
//        qDebug() <<"_____________________________________________________________________________";



//        str = str.mid(10);
//        int size=0;
//        QString body_temp = str.mid(0, 10);
//        QByteArray body = body_temp.toLatin1();
//        qDebug() <<"mmmmmmmmmmmmmmmmmmmmmmmmmmmm";
//        while (body.mid(0,4) != "APIC")
//        {
//            qDebug() <<"nnnnnnnnnnnnnnnnnnnnnnnnnnnnnn";
//            str = str.mid(10);
//            body = str.mid(0, 10).toLatin1();
//            qDebug() <<"n2nnnnnnnnnnnnnnnnnnnnnn";

//        qDebug() << "QQQQQQQQQQQQQQQQQQQQQ";
//        size = body[size+4]  * 0x200000
//             + body[size+5]  * 0x4000
//             + body[size+6]  * 0x20
//             + body[size+7] ;
//             str = str.mid(4);
//             QString temp = str.mid(0, 4);

//             while (temp != "JFIF")
//        {
//                 str = str.mid(4);
//                 temp = str.mid(0, 4);
//         }
//             str = str.mid(4);
//             QString image = str.mid(0, size);

//         qDebug() <<"WWWWWWWWWWWWWWWWWWWWWWWWWWWW";

//             QByteArray array = image.toLatin1();
//             QBuffer buffer(&array);
//             buffer.open(QIODevice::ReadOnly);
//             QImageReader reader(&buffer,"JPG");
//             QImage img = reader.read();

//             ui->pixmap_text_label->setPixmap(QPixmap::fromImage(img));
//             ui->pixmap_text_label->show();



