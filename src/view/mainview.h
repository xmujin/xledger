/**
 * @file mainview.h
 * @author xiangxun
 * @brief 主视图类
 * @date 2026-04-09 13:04:75 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include <QMainWindow>
#include <QObject>

namespace Ui {
    class MainView;
}
class QAbstractItemModel;
struct FilterState;
class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model);
    FilterState getFilterState();

private:
    Ui::MainView *ui;


signals:
    void addBillBtnClicked();
    void addCategoryTagTriggered();
    void filterChanged();
};
