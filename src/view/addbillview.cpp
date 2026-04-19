/**
 * @file addbillview.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:72 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "addbillview.h"
#include "categorydto.h"
#include "tagdto.h"
#include "ui_addbillview.h"
#include "billdto.h"
#include <qdialog.h>
#include <qpushbutton.h>
#include "billdto.h"
#include <QDateTime>
#include <qtmetamacros.h>
#include <qvariant.h>


AddBillView::AddBillView(QWidget *parent, Qt::WindowFlags f)
    : QDialog{parent, f}
    , ui{new Ui::AddBillView}
{

    ui->setupUi(this);
    

    connect(ui->addBillBtn, &QPushButton::clicked, this, &AddBillView::onSubmit);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

}



void AddBillView::onSubmit()
{
    if (ui->moneyLineEdit->text().isEmpty())
    {
        showErrorMessage("请输入金额!");
        return;
    }
    bool ok;
    double money = ui->moneyLineEdit->text().toDouble(&ok);
    if (!ok)
    {
        showErrorMessage("非法输入!");
        ui->moneyLineEdit->clear();
        return;
    }


    // 分类
    int category = ui->categoryComboBox->currentData().toInt();
    int tag = ui->tagComboBox->currentData().toInt();
    
    BillDto dto;
    //dto.date = QDate::currentDate().toString("yyyy-MM-dd");
    dto.amount = money;
    dto.category_id = category;
    dto.note = ui->notePlainTextEdit->toPlainText();
    dto.type = ui->typeComboBox->currentText();
    dto.paytype = ui->payTypeComboBox->currentText();
    dto.tag_id = tag;

    emit addBillClicked(dto);
}

void AddBillView::setCategory(QList<CategoryDto> categories)
{
    ui->categoryComboBox->addItem("无", -1);
    for (auto &category : categories) 
    {
        ui->categoryComboBox->addItem(category.name, category.id);
    }
}


void AddBillView::setTag(QList<TagDto> tags)
{
    ui->tagComboBox->addItem("无", -1);
    for (auto &tag : tags) 
    {
        ui->tagComboBox->addItem(tag.name, tag.id);
    }

}