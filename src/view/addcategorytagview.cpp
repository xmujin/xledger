#include "addcategorytagview.h"
#include "ui_addcategorytagview.h"
#include <QStandardItemModel>
#include <qpushbutton.h>


AddCategoryTagView::AddCategoryTagView(QWidget *parent, Qt::WindowFlags f)
    : QDialog{parent, f}
    , ui{new Ui::AddCategoryTagView}
{
    ui->setupUi(this);

    m_categoryModel = new QStandardItemModel(this);
    ui->categoryListView->setModel(m_categoryModel);
    m_tagModel = new QStandardItemModel(this);
    ui->tagListView->setModel(m_tagModel);

    // 添加账单和标签的按钮触发
    connect(ui->addCategoryBtn, &QPushButton::clicked, this, [this]() {
        emit addCategoryRequest(ui->categoryLineEdit->text());
        ui->categoryLineEdit->clear();
    });

    connect(ui->addTagBtn, &QPushButton::clicked, this, [this]() {
        emit addTagRequest(ui->tagLineEdit->text());
        ui->tagLineEdit->clear();
    });

    // 连接listview的更新
    connect(m_categoryModel, &QStandardItemModel::itemChanged, this, [this](QStandardItem *item) {
        emit updateCategoryRequest(item->data().toInt(), item->text());
    });

    connect(m_tagModel, &QStandardItemModel::itemChanged, this, [this](QStandardItem *item) {
        emit updateTagRequest(item->data().toInt(), item->text());
    });

    // 连接分类和标签的删除
    connect(ui->deleteCategoryBtn, &QPushButton::clicked, this, [this]() {
        QModelIndex index = ui->categoryListView->currentIndex();
        if(index.isValid())
        {
            emit deleteCategoryRequest(index.data(Qt::UserRole + 1).toInt());
        }
        
    });


    connect(ui->deleteTagBtn, &QPushButton::clicked, this, [this]() {
        QModelIndex index = ui->tagListView->currentIndex();
        if(index.isValid())
        {
            emit deleteTagRequest(index.data(Qt::UserRole + 1).toInt());
        }
    });

}

void AddCategoryTagView::setCategory(QList<CategoryDto> categories)
{
    m_categoryModel->clear();
    for (auto &category : categories) 
    {
        QStandardItem *item = new QStandardItem(category.name);
        item->setData(category.id);
        m_categoryModel->appendRow(item);
    }
}

void AddCategoryTagView::setTag(QList<TagDto> tags)
{
    m_tagModel->clear();
    for (auto &tag : tags) 
    {
        QStandardItem *item = new QStandardItem(tag.name);
        item->setData(tag.id);
        m_tagModel->appendRow(item);
    }
}