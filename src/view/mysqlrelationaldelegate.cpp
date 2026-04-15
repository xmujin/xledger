/**
 * @file mysqlrelationaldelegate.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:64 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "mysqlrelationaldelegate.h"

void MySqlRelationalDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QSqlRelationalDelegate::initStyleOption(option, index);
    option->displayAlignment = Qt::AlignCenter;
}
