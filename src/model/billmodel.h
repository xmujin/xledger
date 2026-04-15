#pragma once
#include <QObject>
#include "mysqlrelationaltablemodel.h"

struct BillDto;
class BillModel : public QObject
{
public:
    explicit BillModel(QObject *parent = nullptr);


    /**
     * @brief 初始化模型
     */
    void initModel();
    
    /**
     * @brief 刷新数据
     */
    void loadData();

    /**
     * @brief 设置过滤器
     * @param filter 过滤器的字符串
     */
    void setFilter(const QString &filter);

    /**
     * @brief 添加账单到数据库
     * @param dto 账单的dto
     * @return true 
     * @return false 
     */
    bool addBill(const BillDto &dto);


    /**
     * @brief 初始化QSqlRelationalTableModel
     * @return MySqlRelationalTableModel* 
     */
    MySqlRelationalTableModel* model() const;

private:
    MySqlRelationalTableModel *m_model;

};
