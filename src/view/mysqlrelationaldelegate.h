/**
 * @file mysqlrelationaldelegate.h
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:26 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once

#include <QSqlRelationalDelegate>

class MySqlRelationalDelegate: public QSqlRelationalDelegate
{
    Q_OBJECT

public:
    explicit MySqlRelationalDelegate(QObject *aParent = nullptr)
        : QSqlRelationalDelegate(aParent)
    {}


protected:
    void initStyleOption(QStyleOptionViewItem *option,
                                const QModelIndex &index) const override;




signals:
};
