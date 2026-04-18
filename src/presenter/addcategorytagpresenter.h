/**
 * @file addcategorytagpresenter.h
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:25 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include <QObject>

class ICategoryModel;
class ITagModel;
class IAddView;
class AddCategoryTagPresenter: public QObject
{
    Q_OBJECT

public:
    explicit AddCategoryTagPresenter(ICategoryModel *m_categoryModel, ITagModel *m_tagModel, IAddView *m_view, QObject *parent = nullptr);




public slots:
    void onAddCategoryRequest(const QString& category);
    void onAddTagRequest(const QString& tag);
    void onUpdateCategoryRequest(int id, const QString& name);
    void onUpdateTagRequest(int id, const QString& name);
    void onDeleteCategoryRequest(int id);
    void onDeleteTagRequest(int id);


private:
    ICategoryModel *m_categoryModel;
    ITagModel *m_tagModel;
    IAddView *m_view;
};
