#include "addtabwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "mybutton.h"
#include <QLineEdit>
#include <qlabel.h>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <qmessagebox.h>
#include "mylistwidgetitem.h"



AddTabWidget::AddTabWidget(TabType t, QWidget *parent, Qt::WindowFlags f)
    : m_type{t}
    , QWidget{parent, f}
{
    setContentsMargins(20, 0, 20, 0);

    initUI();
    setupConnections();

}

AddTabWidget::~AddTabWidget()
{
}

void AddTabWidget::initUI()
{
    QVBoxLayout *m_mainLayout = new QVBoxLayout(this);
    QHBoxLayout *m_hLayout = new QHBoxLayout;
    QHBoxLayout *lineEditLayout = new QHBoxLayout;

    m_listWidget = new QListWidget;


    m_listWidget->setFixedHeight(300);
    // 添加列表项

    QSqlQuery query;
    query.exec(QString("select name from %1").arg(m_type == Category ? "category" : "tag"));
  
    while (query.next()) {
        QString name = query.value("name").toString();

        MyListWidgetItem *w = new MyListWidgetItem;
        w->setLabelText(name);

        QListWidgetItem *item = new QListWidgetItem(m_listWidget);
        item->setSizeHint(w->sizeHint());

        m_listWidget->setItemWidget(item, w);

        connect(w, &MyListWidgetItem::btnClicked, this, [=] {
            // 添加是否删除的消息框
            QMessageBox msgBox(this);
            msgBox.setText(QString("是否要删除%1 %2?").arg(m_type == Category ? "分类" : "标签", name));
            msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            if(msgBox.exec() == QMessageBox::Cancel)
            {
                return;
            }

            QSqlQuery query;
            query.prepare(QString("DELETE FROM %1 WHERE name = ?;").arg(m_type == Category ? "category" : "tag"));
            query.addBindValue(name);
            query.exec();
            m_listWidget->takeItem(m_listWidget->row(item)); // 从 list 中移除 item
            delete item; // 删除 item
            delete w;    // 删除 widget
        });
    }
        
    QLabel *headerLabel = new QLabel("当前已有的分类和标签:");
    QLabel *editLabel = new QLabel("请输入分类或标签:");

    m_lineEdit = new QLineEdit;
    m_cancelBtn = new MyButton("取消");
    m_addBtn = new MyButton("添加分类");


    


    //设置按钮尺寸
    m_cancelBtn->setFixedSize(80,30);
    m_addBtn->setFixedSize(80,30);

    m_hLayout->addStretch();
    m_hLayout->addWidget(m_cancelBtn);
    m_hLayout->addSpacing(10);
    m_hLayout->addWidget(m_addBtn);

    // 设置行编辑布局
    lineEditLayout->addWidget(editLabel);
    lineEditLayout->addSpacing(10);
    lineEditLayout->addWidget(m_lineEdit);

    // m_mainLayout->set;
    m_mainLayout->addWidget(headerLabel);
    m_mainLayout->addWidget(m_listWidget);
    m_mainLayout->addLayout(lineEditLayout);
    m_mainLayout->addLayout(m_hLayout);
    m_mainLayout->addStretch();

}

void AddTabWidget::setAddBtnText(const QString &text)
{
    m_addBtn->setText(text);
}


void AddTabWidget::setupConnections()
{


    

    connect(m_addBtn, &MyButton::clicked, this, &AddTabWidget::addBtnClicked);
    connect(m_addBtn, &MyButton::clicked, this, [=] {
        m_lineEdit->clear();
    });


    connect(m_cancelBtn, &MyButton::clicked, this, &AddTabWidget::cancelBtnClicked);

}

QString AddTabWidget::getLineEditText() const
{
    return m_lineEdit->text();
}

void AddTabWidget::addListWidgetItem(const QString &str)
{
    MyListWidgetItem *w = new MyListWidgetItem;
    w->setLabelText(str);

    QListWidgetItem *item = new QListWidgetItem(m_listWidget);
    item->setSizeHint(w->sizeHint());
    m_listWidget->setItemWidget(item, w);
    connect(w, &MyListWidgetItem::btnClicked, this, [=] {
        QMessageBox msgBox(this);
        msgBox.setText(QString("是否要删除%1 %2?").arg(m_type == Category ? "分类" : "标签", str));
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        if(msgBox.exec() == QMessageBox::Cancel)
        {
            return;
        }
        QSqlQuery query;
        query.prepare(QString("DELETE FROM %1 WHERE name = ?;").arg(m_type == Category ? "category" : "tag"));
        query.addBindValue(str);
        query.exec();
        m_listWidget->takeItem(m_listWidget->row(item)); // 从 list 中移除 item
        delete item; // 删除 item
        delete w;    // 删除 widget
    });

}
