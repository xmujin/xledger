#pragma once
#include <QObject>
#include <QDebug>


class MainView;
class BillModel;
class MainPresenter : public QObject
{
    Q_OBJECT

public:
    explicit MainPresenter(BillModel *model, MainView *view, QObject *parent = nullptr);


    void initModel();

private slots:
    void onAddBillBtnClicked();
    void onAddCategoryTagTriggered();
    void applyFilter();

private:
    MainView *m_view;
    BillModel *m_model;
};
