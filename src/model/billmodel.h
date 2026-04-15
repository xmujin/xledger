#pragma once
#include <QObject>

class QSqlRelationalTableModel;
struct BillDto;
class BillModel : public QObject
{
public:
    explicit BillModel(QObject *parent = nullptr);


    // 初始化model
    void initModel();
    
    // 刷新数据
    void loadData();

    // 设置过滤器
    void setFilter(const QString &filter);

    bool addBill(const BillDto &dto);


    QSqlRelationalTableModel* model() const { return m_model; }

private:
    QSqlRelationalTableModel *m_model;

};