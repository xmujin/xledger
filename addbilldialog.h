#pragma once

#include <QObject>
#include <QDialog>



class AddBillDialog: public QDialog
{
    Q_OBJECT

public:
    explicit AddBillDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

signals:
};
