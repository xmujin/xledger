/**
 * @file filterstate.h
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:91 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include <QString>
#include <QDate>


/**
 * @brief 用于收集各个组合框和日期编辑框的状态
 */
struct FilterState
{
    QString billtype; // 全部  收入或支出
    QString dateRange; // 日期范围（今日、近一周、自定义日期范围等）
    QDate start; // 起始日期
    QDate end; // 终止日期
};
