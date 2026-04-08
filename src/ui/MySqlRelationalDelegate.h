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
