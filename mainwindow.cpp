#include "mainwindow.h"
#include "mybutton.h"
#include "mycombobox.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateEdit>
#include <qwidget.h>
#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include "addbilldialog.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1200, 800);
    setWindowTitle("记账系统");

    auto *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu("文件");
    QMenu *aboutMenu = menuBar->addMenu("关于");

    QWidget *w = new QWidget;
    setCentralWidget(w);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *hBoxLayout = new QHBoxLayout;

    MyButton *addBtn = new MyButton("添加账单", this);
    addBtn->setFixedSize(230, 50);

    


    MyComboBox *balComboBox = new MyComboBox;
    MyComboBox *dateComboBox = new MyComboBox;
    balComboBox->setFixedSize(140, 50);
    dateComboBox->setFixedSize(140, 50);
    balComboBox->insertItems(0, QStringList{"全部", "收入", "支出"});
    dateComboBox->insertItems(0, QStringList{"今日", "本周", "本月", "近三月", "全年"});

    QDateEdit *startDateEdit = new QDateEdit;
    QLabel *lable = new QLabel("至");
    QDateEdit *endDateEdit = new QDateEdit;
    startDateEdit->setFixedSize(140, 50);
    endDateEdit->setFixedSize(140, 50);

    startDateEdit->setCalendarPopup(true);
    endDateEdit->setCalendarPopup(true);

    hBoxLayout->addWidget(balComboBox);
    hBoxLayout->addWidget(dateComboBox);
    hBoxLayout->addStretch();
    hBoxLayout->addWidget(startDateEdit);
    hBoxLayout->addWidget(lable);
    hBoxLayout->addWidget(endDateEdit);
    hBoxLayout->addStretch();
    hBoxLayout->addWidget(addBtn);

    QTableView *tableView = new QTableView;
    QStandardItemModel *model = new QStandardItemModel(0, 7, this);
    model->setHorizontalHeaderLabels({"消费时间", "类型", "金额", "分类", "支付方式", "标签", "备注"});
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QList<QStandardItem *> row;
    row << new QStandardItem("2023-10-27") << new QStandardItem("收入") << new QStandardItem("100") << new QStandardItem("工资") << new QStandardItem("微信") << new QStandardItem("奖金") << new QStandardItem("无");
    model->appendRow(row);

    tableView->setModel(model);
    tableView->setFixedHeight(450);

    mainLayout->addStretch(2);
    mainLayout->addLayout(hBoxLayout);
    mainLayout->addStretch(1);
    mainLayout->addWidget(tableView);
    mainLayout->addStretch(5);

    mainLayout->setContentsMargins(80, 0, 80, 0);
    w->setLayout(mainLayout);



    connect(addBtn, &QPushButton::clicked, this, [=]() {
            AddBillDialog abd(this);


            abd.exec();
            


        });

    



}

MainWindow::~MainWindow()
{
}
