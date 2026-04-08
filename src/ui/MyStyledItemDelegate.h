#pragma once

#include <QStyledItemDelegate>

class MyStyledItemDelegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MyStyledItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate{parent} {}
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const override;


signals:
};
