#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qssFile(":/styleSheet.css");//资源文件":/css.qss"
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }

    MainWindow w;
    w.setFixedSize(1000, 664);
    //w.setGeometry(450,75,1000,660);
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    w.show();

    return a.exec();
}
