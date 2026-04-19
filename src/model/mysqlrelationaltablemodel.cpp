/**
 * @file mysqlrelationaltablemodel.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:86 
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "mysqlrelationaltablemodel.h"
#include <QDate>


QVariant MySqlRelationalTableModel::data(const QModelIndex &idx, int role) const
{
    QVariant value = QSqlRelationalTableModel::data(idx, role);
    if(!value.isValid())
    {
        return {};

    }

    //2026 - 04 - 19
    // 改为年月日 
    if (role == Qt::DisplayRole && idx.column() == 1)
    {

        QDate date = QDate::fromString(value.toString(), "yyyy-MM-dd");
        QString result = date.toString("yyyy年M月d日");
        return result;
    }


    if(role == Qt::DisplayRole && idx.column() == 3)
    {
        return value.toString() + "元";
    }

    if(role == Qt::DisplayRole)
    {
        if(value.toString().isEmpty())
        {
            return "无";
        }
    }

    return value;
}
