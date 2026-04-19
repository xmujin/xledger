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
#include <qlogging.h>
#include "ibillmodel.h"
#include "icategorymodel.h"
#include "itagmodel.h"
#include "iaddview.h"
#include <QDate>


AddBillPresenter::AddBillPresenter(IBillModel *billModel, ICategoryModel *categoryModel, ITagModel *tagModel, IAddView *addBillView, QObject *parent)
    : QObject{parent}
    , m_billModel{billModel}
    , m_categoryModel{categoryModel}
    , m_tagModel{tagModel}
    , m_view{addBillView}
{
    m_view->setCategory(m_categoryModel->getCategories());
    m_view->setTag(m_tagModel->getTags());
}


void AddBillPresenter::onSubmitRequest(BillDto dto)
{
	if (dto.amount <= 0)
    {
        m_view->showErrorMessage("金额必须大于0!");
        return;
    }

    // 日期添加
    dto.date = QDate::currentDate().toString("yyyy-MM-dd");

    // TODO 提交添加账单的逻辑
    if(!m_billModel->addBill(dto))
    {
        m_view->showErrorMessage(m_billModel->lastError());
        m_view->reject();
    }
    else
    {
		m_view->accept();
    }
}
