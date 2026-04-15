/**
 * @file addcategorytagpresenter.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:71 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "addcategorytagpresenter.h"
#include "categorymodel.h"
#include "tagmodel.h"
#include "addcategorytagview.h"
#include <qobject.h>

AddCategoryTagPresenter::AddCategoryTagPresenter(CategoryModel *categoryModel, TagModel *tagModel, AddCategoryTagView *view, QObject *parent)
    : m_categoryModel{categoryModel}
    , m_tagModel{tagModel}
    , m_view{view}
    , QObject{parent}
{
    m_view->setCategory(m_categoryModel->getCategories());
    m_view->setTag(m_tagModel->getTags());

    connect(m_view, &AddCategoryTagView::addCategoryRequest, this, [this](const QString &category) {
        m_categoryModel->addCategory(category);
        m_view->setCategory(m_categoryModel->getCategories());
    });
    connect(m_view, &AddCategoryTagView::addTagRequest, this, [this](const QString &tag) {
        m_tagModel->addTag(tag);
        m_view->setTag(m_tagModel->getTags());
    });

    connect(m_view, &AddCategoryTagView::updateCategoryRequest, this, [this](int id, const QString &name) {
        m_categoryModel->updateCategory(id, name);
    });

    connect(m_view, &AddCategoryTagView::updateTagRequest, this, [this](int id, const QString &name) {
        m_tagModel->updateTag(id, name);
    });


    // 删除选中的标签和分类
    connect(m_view, &AddCategoryTagView::deleteCategoryRequest, this, [this](int id) {
        m_categoryModel->deleteCategory(id);
        m_view->setCategory(m_categoryModel->getCategories());
    });


    connect(m_view, &AddCategoryTagView::deleteTagRequest, this, [this](int id) {
        m_tagModel->deleteTag(id);
        m_view->setTag(m_tagModel->getTags());
    });

    
    


}


