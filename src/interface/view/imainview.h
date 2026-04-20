#pragma once

class QAbstractItemModel;
struct FilterState;
class MainPresenter;
class IMainView
{
public: 	
	virtual ~IMainView() = default;
	virtual void setModel(QAbstractItemModel* model) = 0;
	virtual FilterState getFilterState() = 0;
	virtual int showAddCategoryTagWindow(MainPresenter* mainPresenter) = 0;
	virtual int showAddBillWindow() = 0;
};