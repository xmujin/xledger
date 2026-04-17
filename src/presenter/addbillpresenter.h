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


class CategoryModel;
class TagModel;
class BillModel;
class IAddView;
class AddBillPresenter: public QObject
{
    Q_OBJECT

public:
    explicit AddBillPresenter(BillModel *m_billModel, CategoryModel *categoryModel, TagModel *tagModel, IAddView *addBillView, QObject *parent = nullptr);

signals:


public slots:
    void onSubmitRequest(BillDto dto);

private:
    IAddView *m_view;
    BillModel *m_billModel;
    CategoryModel *m_categoryModel;
    TagModel *m_tagModel;
};
