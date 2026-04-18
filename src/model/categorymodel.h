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
#include <QString>
#include "categorydto.h"
#include "icategorymodel.h"

struct CategoryDto;
class CategoryModel: public QObject, public ICategoryModel
{
    Q_OBJECT

public:
    explicit CategoryModel(QObject *parent = nullptr);


    QList<CategoryDto> getCategories() override;

    bool addCategory(const QString &category) override;
    
    bool updateCategory(int id, const QString &name) override;
   
    bool deleteCategory(int id) override;

    bool isExist(const QString& category) override;
private:
    QString m_lastError;
};
