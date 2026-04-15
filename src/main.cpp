#include <QApplication>
#include "database/DatabaseManager.h"
#include "mainview.h"
#include <qfile.h>
#include <QSqlRelationalTableModel>
#include <qlogging.h>
#include <qsqlrelationaltablemodel.h>
#include "mainpresenter.h"
#include "billmodel.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");
    QFile data(":/assets/style.qss");

    if(!data.open(QFile::ReadOnly))
    {
        qWarning() << "打不开";
        return -1;
    }
    QTextStream out(&data);
    a.setStyleSheet(out.readAll());

    // 数据库建表的初始化
    if(!DatabaseManager::init())
    {
        qDebug() << "初始化数据库失败";
    }
    else 
    {
        qDebug() << "初始化数据库成功";
    }


    MainView w;
    BillModel tb;
    MainPresenter mp(&tb, &w);

    w.show();

    return a.exec();
}
