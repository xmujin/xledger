#include <QTest>
#include "databasemanager.h"
#include "billmodel.h"




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
    DatabaseManager::init();
	
}

void TestBillModel::cleanupTestCase()
{
    
}

void TestBillModel::addBill()
{
    BillModel model(this);

    QVERIFY(true);

}


QTEST_MAIN(TestBillModel)
#include "tst_billmodel.moc"