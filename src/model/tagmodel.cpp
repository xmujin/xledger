/**
 * @file tagmodel.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:43 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "TagModel.h"
#include <QSqlQuery>
#include <qcontainerfwd.h>
#include "tagdto.h"

TagModel::TagModel(QObject *parent)
    : QObject{parent}
{
}


QList<TagDto> TagModel::getTags()
{
    QList<TagDto> list;
    QSqlQuery query("SELECT id, name FROM tag");
    while (query.next())
    {
        TagDto dto;
        dto.id = query.value(0).toInt();
        dto.name = query.value(1).toString();
        list.append(dto);
    }
    return list;
}

bool TagModel::addTag(const QString &tag)
{
    QSqlQuery query;
    query.prepare("INSERT INTO tag (name) "
                  "VALUES (?)");
    query.addBindValue(tag);
    query.exec();
    return true;
}

bool TagModel::updateTag(int id, const QString &name)
{
    QSqlQuery query;
    query.prepare("UPDATE tag SET name = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(id);
    query.exec();
    return true;
}

bool TagModel::deleteTag(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tag WHERE id = ?");
    query.addBindValue(id);
    query.exec();
    return true;
}
