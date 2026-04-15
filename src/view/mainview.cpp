/**
 * @file mainview.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:13 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "mainview.h"
#include "filterstate.h"
#include "mysqlrelationaldelegate.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent)
    : QMainWindow{parent}
    , ui{new Ui::MainView}
{
    ui->setupUi(this);
    // 配置日期范围选择

    ui->startDate->setDate(QDate::currentDate());
    ui->endDate->setDate(QDate::currentDate());

    // 隐藏控件
    ui->startDate->hide();
    ui->dateLabel->hide();
    ui->endDate->hide();

    connect(ui->addBillBtn, &MyButton::clicked, this, &MainView::addBillBtnClicked);
    connect(ui->addcategorytag, &QAction::triggered, this, &MainView::addCategoryTagTriggered);


    // 全部 收入 支出
    connect(ui->billTypeComboBox, &MyComboBox::currentTextChanged, this, &MainView::filterChanged);

    // 连接日期组合框(今日、本周等等)
    connect(ui->dateComboBox, &MyComboBox::currentTextChanged, this, [this](const QString &text) {
        if(text == "自定义日期范围")
        {
            ui->startDate->show();
            ui->dateLabel->show();
            ui->endDate->show();
        }
        else 
        {
            ui->startDate->hide();
            ui->dateLabel->hide();
            ui->endDate->hide();
        }
        emit filterChanged();
    });


    connect(ui->startDate, &QDateEdit::userDateChanged, this, &MainView::filterChanged);
    connect(ui->endDate, &QDateEdit::userDateChanged, this, &MainView::filterChanged);
    

}


void MainView::setModel(QAbstractItemModel *model)
{
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0); 
    ui->tableView->setItemDelegate(new MySqlRelationalDelegate(ui->tableView));
}

FilterState MainView::getFilterState()
{
    FilterState fs;
    fs.billtype = ui->billTypeComboBox->currentText();
    fs.dateRange = ui->dateComboBox->currentText();
    fs.start = ui->startDate->date();
    fs.end = ui->endDate->date();
    return fs;
}
