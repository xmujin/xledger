/**
 * @file addtagdialog.h
 * @author xiangxun (xiangxun76@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-04-05
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once

#include <QDialog>
#include <QObject>

class AddTabWidget;
class QSqlQueryModel;
class AddTagDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTagDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());


    void initUI();

    void setupConnections();
signals:


private:
    AddTabWidget *m_category;
    AddTabWidget *m_tag;
    QSqlQueryModel *categoryModel;
    QSqlQueryModel *tagModel;
};
