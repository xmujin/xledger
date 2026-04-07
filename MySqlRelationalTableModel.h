#pragma once

#include <QSqlRelationalTableModel>

class MySqlRelationalTableModel: public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    explicit MySqlRelationalTableModel(QObject *parent = nullptr,
                                      const QSqlDatabase &db = QSqlDatabase())
                                      : QSqlRelationalTableModel{parent, db} {}
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;            

signals:
};
