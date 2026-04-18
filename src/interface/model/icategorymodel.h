#pragma once
#include <QList>


struct CategoryDto;
class ICategoryModel
{
public:
	virtual ~ICategoryModel() = default;
    virtual QList<CategoryDto> getCategories() = 0;

    virtual bool addCategory(const QString& category) = 0;

    virtual bool updateCategory(int id, const QString& name) = 0;

    virtual bool deleteCategory(int id) = 0;

    virtual bool isExist(const QString& category) = 0;

};
