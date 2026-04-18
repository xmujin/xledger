#pragma once
#include "ibillmodel.h"
class MockBillModel : public IBillModel
{
public:

    MOCK_METHOD(void, initModel, (), (override));
    MOCK_METHOD(void, loadData, (), (override));
    MOCK_METHOD(void, setFilter, (const QString& filter), (override));
    MOCK_METHOD(bool, addBill, (const BillDto& dto), (override));
    MOCK_METHOD(QAbstractItemModel*, model, (), (const, override));
    MOCK_METHOD(QString, lastError, (), (const, override));
};