#include "MyStyledItemDelegate.h"

#include <QRect>
#include <QPainter>



void MyStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}
