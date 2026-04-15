/**
 * @file addbillpresenter.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:22 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "AddBillPresenter.h"
#include "addbillview.h"
#include <qlogging.h>
#include "billmodel.h"
#include "categorymodel.h"
#include "tagmodel.h"
AddBillPresenter::AddBillPresenter(BillModel *billModel, CategoryModel *categoryModel, TagModel *tagModel, AddBillView * addBillView, QObject *parent)
    : QObject{parent}
    , m_billModel{billModel}
    , m_categoryModel{categoryModel}
    , m_tagModel{tagModel}
    , m_view{addBillView}
{
    connect(m_view, &AddBillView::addBillClicked, this, &AddBillPresenter::onSubmitRequest);

    m_view->setCategory(m_categoryModel->getCategories());
    m_view->setTag(m_tagModel->getTags());
    

}


void AddBillPresenter::onSubmitRequest(BillDto dto)
{
    // TODO 提交添加账单的逻辑
    m_billModel->addBill(dto);
}
