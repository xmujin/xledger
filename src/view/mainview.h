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
#include "mainview.h"
#include "imainview.h"

namespace Ui {
    class MainView;
}
class QAbstractItemModel;
struct FilterState;
class MainView : public QMainWindow, public IMainView
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model) override;
    FilterState getFilterState() override;
    int showAddCategoryTagWindow() override;
    int showAddBillWindow() override;

private slots:
    void showFileDiaglog();

signals:
    void addBillBtnClicked();
    void addCategoryTagTriggered();
    void filterChanged();
	void exportToExcelRequest(const QString& fileName);
private:
    Ui::MainView *ui;
};
