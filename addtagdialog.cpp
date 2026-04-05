#include "addtagdialog.h"
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "mylistview.h"
#include "mybutton.h"
#include <QLineEdit>
#include "addtabwidget.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
AddTagDialog::AddTagDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog{parent, f}
{
    setFixedSize(500, 550);
    setWindowTitle("添加分类和标签");

    initUI();
    setModel();
    setupConnections();


}

void AddTagDialog::initUI()
{
    QTabWidget *m_tab = new QTabWidget(this);
    m_tab->setFixedSize(width(), height());

    m_category = new AddTabWidget;
    m_tag = new AddTabWidget;
    m_category->setAddBtnText("添加分类");
    m_tag->setAddBtnText("添加账单");


    m_tab->addTab(m_category, "添加分类");
    m_tab->addTab(m_tag, "添加标签");
}

void AddTagDialog::setModel()
{
    categoryModel = new QSqlQueryModel(this);
    categoryModel->setQuery("SELECT id, name FROM category");
    m_category->setModel(categoryModel);

    tagModel = new QSqlQueryModel(this);
    tagModel->setQuery("SELECT id, name FROM tag");
    m_tag->setModel(tagModel);


}

void AddTagDialog::setupConnections()
{
    connect(m_category, &AddTabWidget::addBtnClicked, this, [=]() {
        // TODO 添加分类
        QSqlQuery sb;
        sb.prepare("INSERT INTO category (name) VALUES (?)");
        sb.addBindValue(m_category->getLineEditText());
        sb.exec();
        this->accept();
    });

    connect(m_category, &AddTabWidget::cancelBtnClicked, this, [=]() {
        this->reject();
    });



    connect(m_tag, &AddTabWidget::addBtnClicked, this, [=]() {
        // TODO 添加标签
        QSqlQuery sb;
        sb.prepare("INSERT INTO tag (name) VALUES (?)");
        sb.addBindValue(m_tag->getLineEditText());
        sb.exec();
        this->accept();
    });

    connect(m_tag, &AddTabWidget::cancelBtnClicked, this, [=]() {
        this->reject();
    });

   

}
