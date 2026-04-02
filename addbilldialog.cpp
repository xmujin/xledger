#include "addbilldialog.h"
#include <QFormLayout>
#include "mycombobox.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include "mybutton.h"
#include <QHBoxLayout>


AddBillDialog::AddBillDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog{parent, f}
{

    setFixedSize(520, 500);

    

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *btnLayout = new QHBoxLayout;


    QFormLayout *formLayout = new QFormLayout;

    MyComboBox *category = new MyComboBox(this);
    MyComboBox *tag = new MyComboBox(this);
    MyComboBox *billtype = new MyComboBox(this);
    QLineEdit *money = new QLineEdit(this);
    QTextEdit *note = new QTextEdit(this);
    MyButton *addBtn = new MyButton("创建账单", this);
    MyButton *cancelBtn = new MyButton("取消", this);

    category->setFixedHeight(30);
    tag->setFixedHeight(30);
    billtype->setFixedHeight(30);
    money->setFixedHeight(30);
    // note->setFixedHeight(100);

    addBtn->setFixedSize(150, 50);
    cancelBtn->setFixedSize(150, 50);


    category->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    tag->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    billtype->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    btnLayout->addWidget(cancelBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(addBtn);
    btnLayout->setContentsMargins(50, 0, 50, 0);


    formLayout->addRow("分类:", category);
    formLayout->addRow("标签:", tag);
    formLayout->addRow("支付方式:", billtype);
    formLayout->addRow("消费金额:", money);
    formLayout->addRow("备注:", note);
    

    formLayout->setVerticalSpacing(15);
    formLayout->setHorizontalSpacing(15);

    mainLayout->addLayout(formLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(btnLayout);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    
}
