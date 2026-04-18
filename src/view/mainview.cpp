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
#include <tagmodel.h>
#include <categorymodel.h>
#include <addcategorytagview.h>
#include <addcategorytagpresenter.h>
#include <billmodel.h>
#include <addbillpresenter.h>
#include <QMessageBox>
#include "addbillview.h"

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
    connect(ui->addcategorytag, &QAction::triggered, this, [this] {
        emit addCategoryTagTriggered();
    });

    // 连接关于
    connect(ui->actionabout, &QAction::triggered, this, [this] {
        QMessageBox msgBox(this);
        msgBox.setText("<div>"
                    "<h2 style='color:#3498db;'>XLedger</h2>"
                    "<p style='color:#2ecc71;'>该版本构建于2026年4月，是一款记账软件</p>"
                    "<p style='color:#2ecc71;'>版本: 1.0</p>"
                    "<p style='color:#7f8c8d;'>作者: 向洵</p>"
                    "<p>作者的github地址: <a href='https://github.com/xmujin'>xmujin</a></p>"
                    "</div>");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    });


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


int MainView::showAddCategoryTagWindow()
{
    TagModel tagModel;
    CategoryModel categoryModel;
    AddCategoryTagView view{ this };
    AddCategoryTagPresenter presenter(&categoryModel, &tagModel, &view);
    connect(&view, &AddCategoryTagView::addCategoryRequest, &presenter, &AddCategoryTagPresenter::onAddCategoryRequest);
    connect(&view, &AddCategoryTagView::addTagRequest, &presenter, &AddCategoryTagPresenter::onAddTagRequest);
    connect(&view, &AddCategoryTagView::updateCategoryRequest, &presenter, &AddCategoryTagPresenter::onUpdateCategoryRequest);
    connect(&view, &AddCategoryTagView::updateTagRequest, &presenter, &AddCategoryTagPresenter::onUpdateTagRequest);
    // 删除选中的标签和分类
    connect(&view, &AddCategoryTagView::deleteCategoryRequest, &presenter, &AddCategoryTagPresenter::onDeleteCategoryRequest);
    connect(&view, &AddCategoryTagView::deleteTagRequest, &presenter, &AddCategoryTagPresenter::onDeleteTagRequest);
    
    return view.exec();
}

int MainView::showAddBillWindow()
{
    TagModel tagModel;
    BillModel billModel;
    CategoryModel categoryModel;
    AddBillView view{ this };
    AddBillPresenter presenter(&billModel, &categoryModel, &tagModel, &view);
    connect(&view, &AddBillView::addBillClicked, &presenter, &AddBillPresenter::onSubmitRequest);

    return view.exec();
}