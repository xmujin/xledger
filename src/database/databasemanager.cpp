/**
 * @file databasemanager.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 19:04:01 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "DatabaseManager.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
bool DatabaseManager::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bill.db");
    if(!db.open())
    {
        qDebug() << "打开数据库失败: " << db.lastError();
        return false;
    }
    else
    {
        QSqlQuery query;

        // 启用外键约束
        query.exec("PRAGMA FOREIGN_KEYS=ON;");  

        // 创建标签表
        query.exec(R"(
            CREATE TABLE IF NOT EXISTS tag (
                id INTEGER PRIMARY KEY NOT NULL,
                name TEXT NOT NULL
            );)");

        // 创建分类表
        query.exec(R"(
            CREATE TABLE IF NOT EXISTS category (
                id INTEGER PRIMARY KEY NOT NULL,
                name TEXT NOT NULL
            );)");
        
        // 创建账单表
        query.exec(R"(
            CREATE TABLE IF NOT EXISTS bill (
                id INTEGER PRIMARY KEY NOT NULL,
                date TEXT NOT NULL,
                type TEXT NOT NULL,
                amount REAL NOT NULL,
                category_id INTEGER,
                paytype TEXT NOT NULL,
                tag_id INTEGER,
                note TEXT,

                FOREIGN KEY (category_id) REFERENCES category(id)
                ON DELETE SET NULL
                ON UPDATE CASCADE,

                FOREIGN KEY (tag_id) REFERENCES tag(id)
                ON DELETE SET NULL
                ON UPDATE CASCADE
            );)");
        

        qDebug() << "数据库和表创建成功";
    }

    return true;
}
