#include <QTest>
#include "billdto.h"
#include <gmock/gmock.h>
#include "addbillpresenter.h"
#include "mockaddbillview.h"
#include "mockbillmodel.h"
#include "mockcategorymodel.h"
#include "mocktagmodel.h"


using ::testing::_;      // 匹配符
using ::testing::Return; // 动作

class TestAddBillPresenter : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void onSubmitRequest_fail();
    void onSubmitRequest_success();

protected:
    ::testing::NiceMock<MockAddBillView> view;
    MockBillModel model;
    ::testing::NiceMock<MockCategoryModel> categoryModel;
    ::testing::NiceMock<MockTagModel> tagModel;
};

void TestAddBillPresenter::onSubmitRequest_fail()
{
    EXPECT_CALL(model, addBill(_)).WillOnce(Return(false));
    EXPECT_CALL(model, lastError()).WillOnce(Return(QString("我服了")));
    EXPECT_CALL(view, showErrorMessage(QString("我服了"))).Times(1);

    AddBillPresenter presenter(&model, &categoryModel, &tagModel, &view);
    BillDto bill;
    presenter.onSubmitRequest(bill);
}

void TestAddBillPresenter::onSubmitRequest_success()
{
    EXPECT_CALL(model, addBill(_)).WillOnce(Return(true));
    EXPECT_CALL(view, accept()).Times(1);
    AddBillPresenter presenter(&model, &categoryModel, &tagModel, &view);
    BillDto bill;
    presenter.onSubmitRequest(bill);

}


void TestAddBillPresenter::initTestCase()
{

}

void TestAddBillPresenter::cleanupTestCase()
{

}



QTEST_MAIN(TestAddBillPresenter)
#include "tst_addbillpresenter.moc"