#include "MySqlRelationalDelegate.h"



void MySqlRelationalDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QSqlRelationalDelegate::initStyleOption(option, index);
    option->displayAlignment = Qt::AlignCenter;
}
