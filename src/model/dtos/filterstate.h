#pragma once
#include <QString>
#include <QDate>

struct FilterState
{
    QString billtype; // 全部  收入或支出
    QString dateRange; // 日期范围
    QDate start;
    QDate end;
};
