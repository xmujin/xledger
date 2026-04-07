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
#include <QMessageBox>


AddTagDialog::AddTagDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog{parent, f}
{
    setFixedWidth(500);
    setWindowTitle("添加分类和标签");

    initUI();
    setupConnections();


}

void AddTagDialog::initUI()
{
    // 创建 QTabWidget，不设置固定大小
    QTabWidget *m_tab = new QTabWidget(this);

    // 使用布局管理器，确保 QTabWidget 会自动调整大小
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tab);  // 添加 QTabWidget 到布局中

    m_category = new AddTabWidget(AddTabWidget::Category);
    m_tag = new AddTabWidget(AddTabWidget::Tag);
    m_category->setAddBtnText("添加分类");
    m_tag->setAddBtnText("添加标签");

    // 将两个 AddTabWidget 添加到 QTabWidget 中
    m_tab->addTab(m_category, "添加分类");
    m_tab->addTab(m_tag, "添加标签");

    setLayout(mainLayout);  // 设置主布局
}



void AddTagDialog::setupConnections()
{
    connect(m_category, &AddTabWidget::addBtnClicked, this, [=]() {
        if(m_category->getLineEditText().isEmpty())
        {
            QMessageBox msg(this);
            msg.setText("分类不可以为空！");
            msg.exec();
            return;
        }
        QSqlQuery sb;
        sb.prepare("INSERT INTO category (name) VALUES (?)");
        sb.addBindValue(m_category->getLineEditText());
        sb.exec();

        // 刷新列表
        m_category->addListWidgetItem(m_category->getLineEditText());

    });

    connect(m_category, &AddTabWidget::cancelBtnClicked, this, [=]() {
        this->reject();
    });



    connect(m_tag, &AddTabWidget::addBtnClicked, this, [=]() {
        if(m_tag->getLineEditText().isEmpty())
        {
            QMessageBox msg(this);
            msg.setText("标签不可以为空！");
            msg.exec();
            return;
        }
        QSqlQuery sb;
        sb.prepare("INSERT INTO tag (name) VALUES (?)");
        sb.addBindValue(m_tag->getLineEditText());
        sb.exec();

        // 刷新列表
        m_tag->addListWidgetItem(m_tag->getLineEditText());
    });

    connect(m_tag, &AddTabWidget::cancelBtnClicked, this, [=]() {
        this->reject();
    });

   

}
