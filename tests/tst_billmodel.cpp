#include <QTest>
#include "billmodel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "billdto.h"

class TestBillModel: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void addBill();
};


void TestBillModel::initTestCase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open())
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
	
}

void TestBillModel::cleanupTestCase()
{
    
}

void TestBillModel::addBill()
{
    BillModel model(this);
	BillDto bill;
	bill.amount = 100.0;
	bill.category_id = -1;
    bill.tag_id = -1;
    bill.date = QString("2026年4月");
    bill.note = QString("无");
    bill.paytype = QString("微信支付");
    bill.type = QString("收入");
    model.addBill(bill);
    QSqlQuery query;
    query.exec("select amount from bill where id = 1");
    query.next();
	double get = query.value(0).toDouble();
    QVERIFY(qFuzzyCompare(get, bill.amount));
}





QTEST_MAIN(TestBillModel)
#include "tst_billmodel.moc"