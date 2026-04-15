/**
 * @file categorymodel.h
 * @author xiangxun
 * @brief 分类model
 * @date 2026-04-15 19:04:17 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include <QObject>
#include "categorydto.h"

struct CategoryDto;
class CategoryModel: public QObject
{
    Q_OBJECT

public:
    explicit CategoryModel(QObject *parent = nullptr);

    /**
     * @brief 从数据库中获取分类列表
     * @return QList<CategoryDto> 
     */
    QList<CategoryDto> getCategories();

    /**
     * @brief 添加分类
     * @param category 
     * @return true 
     * @return false 
     */
    bool addCategory(const QString &category);
    
    /**
     * @brief 更新分类
     * @param id 分类id
     * @param name 分类名
     * @return true 
     * @return false 
     */
    bool updateCategory(int id, const QString &name);
    
    /**
     * @brief 删除分类
     * @param id 分类的id
     * @return true 
     * @return false 
     */
    bool deleteCategory(int id);


    signals:
};
