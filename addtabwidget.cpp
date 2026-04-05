#include "addtabwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "mybutton.h"
#include "mylistview.h"
#include <QLineEdit>


AddTabWidget::AddTabWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget{parent, f}
{
    setContentsMargins(50, 0, 50, 0);

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

    m_lineEdit = new QLineEdit;
    m_cancelBtn = new MyButton("取消");
    m_addBtn = new MyButton("添加分类");
    m_hLayout->addWidget(m_cancelBtn);
    m_hLayout->addWidget(m_addBtn);

    m_listView = new MyListView;
    m_mainLayout->addWidget(m_listView);
    m_mainLayout->addWidget(m_lineEdit);
    m_mainLayout->addLayout(m_hLayout);

}

void AddTabWidget::setAddBtnText(const QString &text)
{
    m_addBtn->setText(text);
}

void AddTabWidget::setModel(QAbstractItemModel *model)
{
    m_listView->setModel(model);
    m_listView->setModelColumn(1);
}

void AddTabWidget::setupConnections()
{
    connect(m_addBtn, &MyButton::clicked, this, &AddTabWidget::addBtnClicked);
    connect(m_cancelBtn, &MyButton::clicked, this, &AddTabWidget::cancelBtnClicked);
}

QString AddTabWidget::getLineEditText() const
{
    return m_lineEdit->text();
}
