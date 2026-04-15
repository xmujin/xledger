
#pragma once
#include "billdto.h"
#include <QObject>


class CategoryModel;
class TagModel;
class BillModel;
class AddBillView;
class AddBillPresenter: public QObject
{
    Q_OBJECT

public:
    explicit AddBillPresenter(BillModel *m_billModel, CategoryModel *categoryModel, TagModel *tagModel, AddBillView * addBillView, QObject *parent = nullptr);

signals:


private slots:
    void onSubmitRequest(BillDto dto);

private:
    AddBillView *m_view;
    BillModel *m_billModel;
    CategoryModel *m_categoryModel;
    TagModel *m_tagModel;
};
