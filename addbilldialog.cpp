#include "addbilldialog.h"
#include <QFormLayout>
#include "mycombobox.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include "mybutton.h"
#include <QHBoxLayout>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QStandardItemModel>
#include <QStandardItem>

AddBillDialog::AddBillDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog{parent, f}
{

    setFixedSize(520, 550);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *btnLayout = new QHBoxLayout;

    QFormLayout *formLayout = new QFormLayout;

    MyComboBox *category = new MyComboBox(this);
    MyComboBox *tag = new MyComboBox(this);
    MyComboBox *billtype = new MyComboBox(this);
    MyComboBox *paytype = new MyComboBox(this);
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
    formLayout->addRow("类型:", billtype);
    formLayout->addRow("支付方式:", paytype);
    formLayout->addRow("消费金额:", money);
    formLayout->addRow("备注:", note);

    formLayout->setVerticalSpacing(15);
    formLayout->setHorizontalSpacing(15);

    mainLayout->addLayout(formLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(btnLayout);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // 添加数据到combobox里面
    paytype->addItem("微信");
    paytype->addItem("支付宝");
    paytype->addItem("现金");

    billtype->addItem("收入");
    billtype->addItem("支出");

    // category
    QStandardItemModel *categoryModel = new QStandardItemModel(this);
    categoryModel->appendRow(new QStandardItem("无"));
    QSqlQuery queryCategory("SELECT name FROM category");
    while (queryCategory.next())
    {
        categoryModel->appendRow(new QStandardItem(queryCategory.value(0).toString()));
    }

    category->setModel(categoryModel);

    // tag
    QStandardItemModel *tagModel = new QStandardItemModel(this);
    tagModel->appendRow(new QStandardItem("无"));
    QSqlQuery queryTag("SELECT name FROM tag");
    while (queryTag.next())
    {
        tagModel->appendRow(new QStandardItem(queryTag.value(0).toString()));
    }

    tag->setModel(tagModel);

    // 取消按钮
    connect(cancelBtn, &QPushButton::clicked, this, &AddBillDialog::reject);

    // 添加账单按钮逻辑
    connect(addBtn, &QPushButton::clicked, this, [=]()
            {
                QSqlQuery query;
                query.prepare("INSERT INTO bill (date, type, amount, category_id, paytype,tag_id, note) "
                              "VALUES (?, ?, ?, ?, ?, ?, ?)");
                query.addBindValue(QDate::currentDate().toString("yyyy-MM-dd")); // 日期
                query.addBindValue(billtype->currentText());                     // 收入 或 支出
                query.addBindValue(money->text().toDouble());                    // 金额

                if (category->currentText() != "无")
                {
                    query.addBindValue(category->model()->index(category->currentIndex(), 0).data().toInt()); // 分类id
                }
                else
                {
                    query.addBindValue(QVariant());
                }

                query.addBindValue(paytype->currentText()); // 支付方式

                if (tag->currentText() != "无")
                {
                    query.addBindValue(tag->model()->index(tag->currentIndex(), 0).data().toInt()); // 标签id
                }
                else
                {
                    query.addBindValue(QVariant());
                }

                query.addBindValue(note->toPlainText());
                query.exec();

                this->accept(); // 关闭对话框
            });
}
