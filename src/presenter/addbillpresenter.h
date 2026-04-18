/**
 * @file addbillpresenter.h
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:97 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include "billdto.h"
#include <QObject>


class ICategoryModel;
class ITagModel;
class IBillModel;
class IAddView;
class AddBillPresenter: public QObject
{
    Q_OBJECT

public:
    explicit AddBillPresenter(IBillModel *m_billModel, ICategoryModel *categoryModel, ITagModel *tagModel, IAddView *addBillView, QObject *parent = nullptr);

signals:


public slots:
    void onSubmitRequest(BillDto dto);

private:
    IAddView *m_view;
    IBillModel *m_billModel;
    ICategoryModel *m_categoryModel;
    ITagModel *m_tagModel;
};
