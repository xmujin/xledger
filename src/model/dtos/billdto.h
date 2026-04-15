#pragma once
#include <QString>

struct BillDto
{
    QString date;
    QString type;
    double amount;
    int category_id;
    QString paytype;
    int tag_id;
    QString note;
    BillDto() = default;
};