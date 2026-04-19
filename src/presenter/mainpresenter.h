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
class IBillModel;
class AddCategoryTagView;
class MainPresenter : public QObject
{
    Q_OBJECT

public:
    explicit MainPresenter(IBillModel *model, IMainView* view, QObject *parent = nullptr);


    void initModel();

public slots:
    void onAddBillBtnClicked();
    void onAddCategoryTagTriggered();
    void onExportToExcelRequest(const QString& fileName);
    void applyFilter();

private:
    IMainView *m_view;
	AddCategoryTagView* m_addCategoryTagView;
    IBillModel *m_model;
};
