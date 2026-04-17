/**
 * @file mainpresenter.cpp
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:12 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "mainpresenter.h"
#include "CategoryModel.h"
#include "TagModel.h"
#include "addbillpresenter.h"
#include "addcategorytagpresenter.h"
#include "billmodel.h"
#include "filterstate.h"
#include "imainview.h"
#include <QDialog>


MainPresenter::MainPresenter(BillModel *model, IMainView *view, QObject* parent)
    : QObject{ parent }, m_model{ model }, m_view{ view }
{
    initModel();

}


void MainPresenter::initModel()
{
    m_view->setModel(m_model->model());
    m_model->loadData();
    // 调用过滤器
    applyFilter();
}

void MainPresenter::onAddBillBtnClicked() {
	if (m_view->showAddBillWindow() == QDialog::Accepted)
    {
        // 刷新数据
        m_model->loadData();
    }
}

void MainPresenter::onAddCategoryTagTriggered()
{
    if (m_view->showAddCategoryTagWindow() == QDialog::Accepted)
    {
    }
}

void MainPresenter::applyFilter()
{
    // 获取当前状态
    FilterState fs = m_view->getFilterState();
    QStringList filters;
    // 全部  收入  支出的过滤
    if (fs.billtype == "全部")
    {
        filters << QString("type IN ('收入', '支出')");
    
    }
    else if(fs.billtype == "支出")
    {
        filters << QString("type = '支出'");
    }
    else if(fs.billtype == "收入")
    {

        filters << QString("type = '收入'");
    }

    // 今日, 本周, 本月, 近三月, 全年的过滤
    if (fs.dateRange == "今日")
    {
        filters << QString("date = date('now')");
    
    }
    else if (fs.dateRange == "本周")
    {
        filters << QString("date >= date('now','weekday 0','-6 days')");
    }
    else if (fs.dateRange == "本月")
    {
        filters << QString("strftime('%Y-%m', date) = strftime('%Y-%m','now')");
    }
    else if (fs.dateRange == "近三月")
    {
        filters << QString("date >= date('now','-3 month')");
    }
    else if (fs.dateRange == "全年")
    {
        filters << QString("strftime('%Y',date) = strftime('%Y','now')");
    }
    else if (fs.dateRange == "自定义日期范围")
    {
        
        filters << QString("date between '%1' and '%2'")
        .arg(fs.start.toString("yyyy-MM-dd"))
        .arg(fs.end.toString("yyyy-MM-dd"));

        qDebug() << QString("date between '%1' and '%2'")
        .arg(fs.start.toString("yyyy-MM-dd"))
        .arg(fs.end.toString("yyyy-MM-dd"));
    }
    QString filterStr = filters.join(" AND ");
    m_model->setFilter(filterStr);
}
