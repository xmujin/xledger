/**
 * @file addcategorytagview.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:36 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "addcategorytagview.h"
#include "ui_addcategorytagview.h"
#include <QStandardItemModel>
#include <QMessageBox>


AddCategoryTagView::AddCategoryTagView(QWidget *parent, Qt::WindowFlags f)
    : QDialog{parent, f}
    , ui{new Ui::AddCategoryTagView}
    , m_categoryModel{ new QStandardItemModel(this) }
    , m_tagModel { new QStandardItemModel(this) }
{
    ui->setupUi(this);
    // 设置按钮颜色
    ui->deleteCategoryBtn->setButtonColors(QColor("#DC3545"), QColor("#C82333"), QColor("#A01E28"));
    ui->deleteTagBtn->setButtonColors(QColor("#DC3545"), QColor("#C82333"), QColor("#A01E28"));
    
    // 设置model到listview
    ui->categoryListView->setModel(m_categoryModel);
    ui->tagListView->setModel(m_tagModel);


    // 添加账单和标签的按钮触发
    connect(ui->addCategoryBtn, &MyButton::clicked, this, [this]() {
        if(ui->categoryLineEdit->text().isEmpty())
        {
            showErrorMessage("分类名称不能为空");
            return;
        }

        emit addCategoryRequest(ui->categoryLineEdit->text());
        ui->categoryLineEdit->clear();
    });

    connect(ui->addTagBtn, &MyButton::clicked, this, [this]() {
        if (ui->tagLineEdit->text().isEmpty())
        {
            showErrorMessage("标签名称不能为空");
            return;
        }
        emit addTagRequest(ui->tagLineEdit->text());
        ui->tagLineEdit->clear();
    });


    // 连接listview的更新
    connect(m_categoryModel, &QStandardItemModel::itemChanged, this, [this](QStandardItem *item) {
		if (item->text().isEmpty())
        {
			showErrorMessage("分类名称不能为空");
            // 恢复原来的分类名
			item->setText(item->data(UserData::BackUpRole).toString());
            return;
        }
        emit updateCategoryRequest(item->data(UserData::IdRole).toInt(), item->text());
    });

    connect(m_tagModel, &QStandardItemModel::itemChanged, this, [this](QStandardItem *item) {
        if (item->text().isEmpty())
        {
            showErrorMessage("标签名称不能为空");

            // 恢复原来的标签名
            item->setText(item->data(UserData::BackUpRole).toString());
            return;
        }
        emit updateTagRequest(item->data(UserData::IdRole).toInt(), item->text());
    });

    // 连接分类和标签的删除
    connect(ui->deleteCategoryBtn, &QPushButton::clicked, this, [this]() {
        QModelIndex index = ui->categoryListView->currentIndex();
        if(index.isValid())
        {
            emit deleteCategoryRequest(index.data(UserData::IdRole).toInt());
        }
        
    });


    connect(ui->deleteTagBtn, &QPushButton::clicked, this, [this]() {
        QModelIndex index = ui->tagListView->currentIndex();
        if(index.isValid())
        {
            emit deleteTagRequest(index.data(UserData::IdRole).toInt());
        }
    });

}

void AddCategoryTagView::setCategory(QList<CategoryDto> categories)
{
    m_categoryModel->clear();
    for (auto &category : categories) 
    {
        QStandardItem *item = new QStandardItem(category.name);
        item->setData(category.id, UserData::IdRole);
        item->setData(category.name, UserData::BackUpRole);
        m_categoryModel->appendRow(item);
    }
}

void AddCategoryTagView::setTag(QList<TagDto> tags)
{
    m_tagModel->clear();
    for (auto &tag : tags) 
    {
        QStandardItem *item = new QStandardItem(tag.name);
        item->setData(tag.id, UserData::IdRole);
        item->setData(tag.name, UserData::BackUpRole);
        m_tagModel->appendRow(item);
    }
}

void AddCategoryTagView::resetName(int id, Type t)
{
    QStandardItemModel* model =
        (t == Type::Tag) ? m_tagModel : m_categoryModel;

    for (int i = 0; i < model->rowCount(); ++i)
    {
        auto item = model->item(i);

        if (item->data(UserData::IdRole).toInt() == id)
        {
            QSignalBlocker blocker(model);
            item->setText(item->data(UserData::BackUpRole).toString());
            return;
        }
    }
}


