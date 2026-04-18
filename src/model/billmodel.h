#pragma once
#include <QObject>
#include "ibillmodel.h"

struct BillDto;
class QSqlRelationalTableModel;
class QAbstractItemModel;
class BillModel : public QObject, public IBillModel
{
public:
    explicit BillModel(QObject *parent = nullptr);


    /**
     * @brief 初始化模型
     */
    void initModel() override;
    
    /**
     * @brief 刷新数据
     */
    void loadData() override;

    /**
     * @brief 设置过滤器
     * @param filter 过滤器的字符串
     */
    void setFilter(const QString &filter) override;

    /**
     * @brief 添加账单到数据库
     * @param dto 账单的dto
     * @return true 
     * @return false 
     */
    bool addBill(const BillDto &dto) override;


    /**
     * @brief 初始化QSqlRelationalTableModel
     * @return MySqlRelationalTableModel* 
     */
    QAbstractItemModel* model() const override;

	QString lastError() const override { return m_lastError; }
private:
    QSqlRelationalTableModel* m_model;
	QString m_lastError;
  


};
