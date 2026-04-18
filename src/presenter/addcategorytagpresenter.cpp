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
#include "icategorymodel.h"
#include "itagmodel.h"
#include "iaddview.h"
#include <QObject>

AddCategoryTagPresenter::AddCategoryTagPresenter(ICategoryModel *categoryModel, ITagModel *tagModel, IAddView *view, QObject *parent)
    : m_categoryModel{categoryModel}
    , m_tagModel{tagModel}
    , m_view{view}
    , QObject{parent}
{
    m_view->setCategory(m_categoryModel->getCategories());
    m_view->setTag(m_tagModel->getTags());
}


void AddCategoryTagPresenter::onAddCategoryRequest(const QString& category)
{
    if (m_categoryModel->isExist(category))
    {
        m_view->showErrorMessage("分类已存在");
		return;
    }

    m_categoryModel->addCategory(category);
    m_view->setCategory(m_categoryModel->getCategories());
}


void AddCategoryTagPresenter::onAddTagRequest(const QString& tag)
{
    if (m_tagModel->isExist(tag))
    {
        m_view->showErrorMessage("标签已存在");
        return;
    }
    m_tagModel->addTag(tag);
    m_view->setTag(m_tagModel->getTags());
}

void AddCategoryTagPresenter::onUpdateCategoryRequest(int id, const QString& name)
{
    m_categoryModel->updateCategory(id, name);
    m_view->setCategory(m_categoryModel->getCategories());
}

void AddCategoryTagPresenter::onUpdateTagRequest(int id, const QString& name)
{
    m_tagModel->updateTag(id, name);
    m_view->setTag(m_tagModel->getTags());
}

void AddCategoryTagPresenter::onDeleteCategoryRequest(int id)
{
    m_categoryModel->deleteCategory(id);
    m_view->setCategory(m_categoryModel->getCategories());
}

void AddCategoryTagPresenter::onDeleteTagRequest(int id)
{
    m_tagModel->deleteTag(id);
    m_view->setTag(m_tagModel->getTags());
}
