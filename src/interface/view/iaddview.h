


#pragma once
#include <QList>
#include "categorydto.h"
#include "tagdto.h"
#include <QMessageBox>
#include <QString>
#include <QDialog>

class IAddView
{
public:
	virtual void setCategory(QList<CategoryDto> categories) = 0;
	virtual void setTag(QList<TagDto> tags) = 0;
	virtual QWidget* widget() = 0;
	virtual void showErrorMessage(const QString& message)
	{
		QMessageBox::warning(widget(), "提示", message);
	}
	virtual void accept() {}
	virtual void reject() {}
};