#pragma once
#include "icategorymodel.h"
class MockCategoryModel : public ICategoryModel
{
public:
    MOCK_METHOD(QList<CategoryDto>, getCategories, (), (override));
    MOCK_METHOD(bool, addCategory, (const QString& category), (override));
    MOCK_METHOD(bool, updateCategory, (int id, const QString& name), (override));
    MOCK_METHOD(bool, deleteCategory, (int id), (override));
    MOCK_METHOD(bool, isExist, (const QString& category), (override));
};