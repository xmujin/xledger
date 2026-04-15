/**
 * @file billdto.h
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:21 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include <QString>

/**
 * @brief 账单的Dto
 */
struct BillDto
{
    QString date; // 日期
    QString type; // 账单类型(收入或支出)
    double amount; // 金额
    int category_id; // 分类id
    QString paytype; // 支付方式
    int tag_id; // 标签id
    QString note; // 备注
    BillDto() = default;
};