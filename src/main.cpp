/**
 * @file main.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:70 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <QApplication>
#include "databasemanager.h"
#include "mainview.h"
#include <QFile>
#include <QDebug>
#include "mainpresenter.h"
#include "billmodel.h"
#include "mysqlrelationaltablemodel.h"
#include "addcategorytagview.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");
    QApplication::setWindowIcon(QIcon(":/resources/favicon.ico"));

    QFile data(":/resources/style.qss");

    if(!data.open(QFile::ReadOnly))
    {
        qWarning() << "打不开啊sdfsdf";
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
    QObject::connect(&w, &MainView::addBillBtnClicked, &mp, &MainPresenter::onAddBillBtnClicked);
    QObject::connect(&w, &MainView::addCategoryTagTriggered, &mp, &MainPresenter::onAddCategoryTagTriggered);
    QObject::connect(&w, &MainView::filterChanged, &mp, &MainPresenter::applyFilter);
    QObject::connect(&w, &MainView::exportToExcelRequest, &mp, &MainPresenter::onExportToExcelRequest);

    w.show();
    return a.exec();
}

