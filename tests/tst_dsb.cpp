#include <QTest>

class TestDsb: public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
};

void TestDsb::toUpper()
{
    QString str = "Hello";
    QVERIFY(str.toLower() == "hello");
}

QTEST_MAIN(TestDsb)
#include "tst_dsb.moc"