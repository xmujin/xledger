#pragma once


struct BillDto;
class QAbstractItemModel;
class QString;
class IBillModel
{
public:
    virtual void initModel() = 0;
    virtual void loadData() = 0;
    virtual void setFilter(const QString& filter) = 0;
    virtual bool addBill(const BillDto& dto) = 0;
    virtual QAbstractItemModel* model() const = 0;
    virtual QString lastError() const = 0;
};
