#include "categorymodel.h"
/**
 * @file categorymodel.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:82 
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "categorydto.h"
#include <QSqlQuery>
#include <QSqlError>


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
    bool success = query.exec();
    if(!success)
    {
        m_lastError = query.lastError().text();
	}
    return success;
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

bool CategoryModel::isExist(const QString& category)
{
    QSqlQuery query;
    query.exec(QString("SELECT id FROM category WHERE name = '%1'").arg(category));
    if (query.next())
    {
        return true;
    }
    return false;
}
