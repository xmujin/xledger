/**
 * @file mainpresenter.h
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:92 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include <QObject>
#include <QDebug>


class IMainView;
class BillModel;
class AddCategoryTagView;
class MainPresenter : public QObject
{
    Q_OBJECT

public:
    explicit MainPresenter(BillModel *model, IMainView* view, QObject *parent = nullptr);


    void initModel();

public slots:
    void onAddBillBtnClicked();
    void onAddCategoryTagTriggered();
    void applyFilter();

private:
    IMainView *m_view;
	AddCategoryTagView* m_addCategoryTagView;
    BillModel *m_model;
};
