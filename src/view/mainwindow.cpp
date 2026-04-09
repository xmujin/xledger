#include "mainwindow.h"
#include "mybutton.h"
#include "mycombobox.h"
#include <QHBoxLayout>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDateEdit>
#include <qwidget.h>
#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include "addbilldialog.h"
#include <QMenuBar>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include "addtagdialog.h"
#include <qsqlrelationaldelegate.h>
#include "mysqlrelationaldelegate.h"
#include "mysqlrelationaltablemodel.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui{new Ui::MainWindow}
{
    initBase();
    connectDb();
    createMenu();
    createMainLayout();
    createHBoxLayout();
    createTableView();
    setupConnections();
}

void MainWindow::initBase()
{
    setFixedSize(1200, 800);
    setWindowTitle("记账系统");
}

void MainWindow::connectDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bill.db");
    if(!db.open())
    {
        qDebug() << "打开数据库失败: " << db.lastError();
    }
    else
    {
        QSqlQuery query;

        // 启用外键约束
        query.exec("PRAGMA FOREIGN_KEYS=ON;");  

        // 创建标签表
        query.exec(R"(
            CREATE TABLE IF NOT EXISTS tag (
                id INTEGER PRIMARY KEY NOT NULL,
                name TEXT NOT NULL
            );)");

        // 创建分类表
        query.exec(R"(
            CREATE TABLE IF NOT EXISTS category (
                id INTEGER PRIMARY KEY NOT NULL,
                name TEXT NOT NULL
            );)");
        
        // 创建账单表
        query.exec(R"(
            CREATE TABLE IF NOT EXISTS bill (
                id INTEGER PRIMARY KEY NOT NULL,
                date TEXT NOT NULL,
                type TEXT NOT NULL,
                amount REAL NOT NULL,
                category_id INTEGER,
                paytype TEXT NOT NULL,
                tag_id INTEGER,
                note TEXT,
                FOREIGN KEY (category_id) REFERENCES category(id)
                ON DELETE CASCADE
                ON UPDATE CASCADE,
                FOREIGN KEY (tag_id) REFERENCES tag(id)
                ON DELETE CASCADE
                ON UPDATE CASCADE
            );)");
        

        qDebug() << "数据库和表创建成功";
    }

    // 插入种子数据
    #if 0
    QSqlQuery query;
    query.prepare("INSERT INTO tag (name) "
                  "VALUES (?)");
    query.addBindValue("早餐");
    query.exec();
    query.addBindValue("中餐");
    query.exec();
    query.addBindValue("晚餐");
    query.exec();
    query.addBindValue("公交车");
    query.exec();
    query.addBindValue("出租车");
    query.exec();

    query.prepare("INSERT INTO category (name) "
                  "VALUES (?)");
    query.addBindValue("饮食");
    query.exec();
    query.addBindValue("出行");
    query.exec();




    query.prepare("INSERT INTO bill (date, type, amount, category_id, paytype,tag_id, note) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue("2026-04-05");
    query.addBindValue("支出");
    query.addBindValue(100);
    query.addBindValue(1);
    query.addBindValue("微信");    
    query.addBindValue(1);
    query.addBindValue("无");
    query.exec();


    #endif
    


    


}

void MainWindow::createMenu()
{
    auto *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu("文件");
    QMenu *settingMenu = menuBar->addMenu("设置");
    QMenu *aboutMenu = menuBar->addMenu("关于");

    // 菜单项
    QAction *actAdd = settingMenu->addAction("添加分类和标签");


    connect(actAdd, &QAction::triggered, this, [=]() {
        AddTagDialog atd(this);
        atd.exec();
    });

}

void MainWindow::createMainLayout()
{
    QWidget *w = new QWidget;
    setCentralWidget(w);
    QVBoxLayout *mainLayout = new QVBoxLayout(w);

    // 添加水平布局和表格控件
    hBoxLayout = new QHBoxLayout;
    tableView = new QTableView;

    mainLayout->addStretch(2);
    mainLayout->addLayout(hBoxLayout);
    mainLayout->addStretch(1);
    mainLayout->addWidget(tableView);
    mainLayout->addStretch(5);
    mainLayout->setContentsMargins(80, 0, 80, 0);
}

void MainWindow::createHBoxLayout()
{
    addBtn = new MyButton("添加账单", this);
    

    balComboBox = new QComboBox;
    dateComboBox = new MyComboBox;
    startDateEdit = new QDateEdit;
    lable = new QLabel("至");
    endDateEdit = new QDateEdit;

    // 尺寸设置
    addBtn->setFixedSize(150, 30);
    balComboBox->setFixedSize(140, 30);
    dateComboBox->setFixedSize(140, 30);
    startDateEdit->setFixedSize(140, 30);
    endDateEdit->setFixedSize(140, 30);

    // 组合框设置
    balComboBox->insertItems(0, QStringList{"全部", "收入", "支出"});
    dateComboBox->insertItems(0, QStringList{"今日", "本周", "本月", "近三月", "全年", "自定义日期范围"});



    
    // 日期选择框设置
    startDateEdit->setDate(QDate(QDate::currentDate().year(), 1, 1));
    endDateEdit->setDate(QDate::currentDate());
    // 显示下拉日期选择框
    startDateEdit->setCalendarPopup(true);
    endDateEdit->setCalendarPopup(true);
    startDateEdit->hide();
    endDateEdit->hide();

    // 标签隐藏
    lable->hide();



    // 水平布局设置
    hBoxLayout->addWidget(balComboBox);
    hBoxLayout->addWidget(dateComboBox);
    hBoxLayout->addWidget(startDateEdit);
    hBoxLayout->addWidget(lable);
    hBoxLayout->addWidget(endDateEdit);
    hBoxLayout->addStretch();
    hBoxLayout->addWidget(addBtn);

}

void MainWindow::createTableView()
{
    tableView->setFixedHeight(450);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // model设置
    model = new MySqlRelationalTableModel;
    model->setTable("bill"); 
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 设置外键关系
    model->setRelation(4, QSqlRelation("category", "id", "name"));
    model->setRelation(6, QSqlRelation("tag", "id", "name"));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);  // 关键
    // 添加表格头
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("消费时间"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("类型"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("金额"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("分类"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("支付方式"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("标签"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("备注"));
    
    // 设置模型
    tableView->setModel(model);
    tableView->hideColumn(0); 
    tableView->setItemDelegate(new MySqlRelationalDelegate(tableView));


    

    // 更新数据
    updateFilter();
    model->select();
    
}

void MainWindow::setupConnections()
{
    connect(addBtn, &QPushButton::clicked, this, [=]() {
            AddBillDialog abd(this);
            if (abd.exec() == QDialog::Accepted) {
                model->select(); // 只有用户点击添加并成功插入时才刷新
            }

        });

    // 连接下拉列表的过滤
    connect(balComboBox, QOverload<int>::of(&MyComboBox::currentIndexChanged), this, &MainWindow::updateFilter);
    connect(dateComboBox, QOverload<int>::of(&MyComboBox::currentIndexChanged), this, &MainWindow::updateFilter);
    connect(startDateEdit, &QDateEdit::dateChanged, this, &MainWindow::updateFilter);
    connect(endDateEdit, &QDateEdit::dateChanged, this, &MainWindow::updateFilter);

    
}

void MainWindow::updateFilter()
{
    if(dateComboBox->currentText() != "自定义日期范围")
    {
        startDateEdit->hide();
        endDateEdit->hide();
        lable->hide();
    }
    else 
    {
        startDateEdit->show();
        endDateEdit->show();
        lable->show();
    }


    QStringList filters;

    // 全部  收入  支出的过滤
    if (balComboBox->currentText() == "全部")
    {
        filters << QString("type IN ('收入', '支出')");
    
    }
    else if (balComboBox->currentText() == "支出")
    {
        filters << QString("type = '支出'");
    }
    else if (balComboBox->currentText() == "收入")
    {

        filters << QString("type = '收入'");
    }

    // 今日, 本周, 本月, 近三月, 全年的过滤
    if (dateComboBox->currentText() == "今日")
    {
        filters << QString("date = date('now')");
    
    }
    else if (dateComboBox->currentText() == "本周")
    {
        filters << QString("date >= date('now','weekday 0','-6 days')");
    }
    else if (dateComboBox->currentText() == "本月")
    {
        filters << QString("strftime('%Y-%m', date) = strftime('%Y-%m','now')");
    }
    else if (dateComboBox->currentText() == "近三月")
    {
        filters << QString("date >= date('now','-3 month')");
    }
    else if (dateComboBox->currentText() == "全年")
    {
        filters << QString("strftime('%Y',date) = strftime('%Y','now')");
    }
    else if (dateComboBox->currentText() == "自定义日期范围")
    {
        
        filters << QString("date between '%1' and '%2'")
        .arg(startDateEdit->date().toString("yyyy-MM-dd"))
        .arg(endDateEdit->date().toString("yyyy-MM-dd"));

        qDebug() << QString("date between '%1' and '%2'")
        .arg(startDateEdit->date().toString("yyyy-MM-dd"))
        .arg(endDateEdit->date().toString("yyyy-MM-dd"));
    }
    
    
    QString filterStr = filters.join(" AND ");
    model->setFilter(filterStr);
    model->select(); // 刷新数据    

}

MainWindow::~MainWindow()
{

    delete ui;

    // FIXME 将model改为智能指针来释放
    model->submitAll();
    delete model; 

    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");



}
