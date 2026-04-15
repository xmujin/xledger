/**
 * @file categorymodel.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:82 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "CategoryModel.h"
#include "dtos/categorydto.h"
#include <QSqlQuery>


CategoryModel::CategoryModel(QObject *parent)
    : QObject{parent}
{
}


QList<CategoryDto> CategoryModel::getCategories()
{
    QList<CategoryDto> list;
    QSqlQuery query("SELECT id, name FROM category");
    while (query.next())
    {
        CategoryDto dto;
        dto.id = query.value(0).toInt();
        dto.name = query.value(1).toString();
        list.append(dto);
    }
    return list;
}

bool CategoryModel::addCategory(const QString &category)
{
    QSqlQuery query;
    query.prepare("INSERT INTO category (name) "
                  "VALUES (?)");
    query.addBindValue(category);
    query.exec();
    return true;
}


bool CategoryModel::updateCategory(int id, const QString &name)
{

    QSqlQuery query;
    query.prepare("UPDATE category SET name = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(id);
    query.exec();
    return true;
}

bool CategoryModel::deleteCategory(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM category WHERE id = ?");
    query.addBindValue(id);
    query.exec();
    return false;
}
