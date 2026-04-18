#pragma once
#include "itagmodel.h"

class MockTagModel : public ITagModel
{
public:
    MOCK_METHOD(bool, addTag, (const QString& tag), (override));
    MOCK_METHOD(bool, updateTag, (int id, const QString& name), (override));
    MOCK_METHOD(bool, deleteTag, (int id), (override));
    MOCK_METHOD(bool, isExist, (const QString& tag), (override));
    MOCK_METHOD(QList<TagDto>, getTags, (), (override));
};
