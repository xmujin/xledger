/**
 * @file billmodel.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:96 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "billmodel.h"
#include "billdto.h"
#include <QSqlQuery>
#include <QSqlRelationalTableModel>

BillModel::BillModel( QObject* parent)
    : QObject{parent}
    , m_model{ new QSqlRelationalTableModel }
{
    initModel();
}



void BillModel::initModel()
{
    m_model->setTable("bill"); 
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // 设置外键关系
    m_model->setRelation(4, QSqlRelation("category", "id", "name"));
    m_model->setRelation(6, QSqlRelation("tag", "id", "name"));
    m_model->setJoinMode(QSqlRelationalTableModel::LeftJoin);  // 关键
    // 添加表格头
    m_model->setHeaderData(1, Qt::Horizontal, QObject::tr("消费时间"));
    m_model->setHeaderData(2, Qt::Horizontal, QObject::tr("类型"));
    m_model->setHeaderData(3, Qt::Horizontal, QObject::tr("金额"));
    m_model->setHeaderData(4, Qt::Horizontal, QObject::tr("分类"));
    m_model->setHeaderData(5, Qt::Horizontal, QObject::tr("支付方式"));
    m_model->setHeaderData(6, Qt::Horizontal, QObject::tr("标签"));
    m_model->setHeaderData(7, Qt::Horizontal, QObject::tr("备注"));
}



void BillModel::loadData()
{
    m_model->select();
}

void BillModel::setFilter(const QString &filter)
{
    m_model->setFilter(filter);
}

bool BillModel::addBill(const BillDto &dto)
{
    QSqlQuery query;
    query.prepare("INSERT INTO bill (date, type, amount, category_id, paytype,tag_id, note) "
                    "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(dto.date); // 日期
    query.addBindValue(dto.type);                     // 收入 或 支出
    query.addBindValue(dto.amount);                    // 金额
    if(dto.category_id != -1)
    {
        query.addBindValue(dto.category_id);
    }
    else 
    {
        query.addBindValue(QVariant());
    }
    query.addBindValue(dto.paytype);
    if(dto.tag_id != -1)
    {
        query.addBindValue(dto.tag_id);
    }
    else 
    {
        query.addBindValue(QVariant());
    }
    query.addBindValue(dto.note);
    if(!query.exec())
    {
        return false;
    }
    return true;
}

QAbstractItemModel* BillModel::model() const
{
    return m_model;
}
