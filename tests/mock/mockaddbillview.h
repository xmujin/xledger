#pragma once
#include "iaddview.h"
class MockAddBillView : public IAddView
{
public:
    MOCK_METHOD(void, setCategory, (QList<CategoryDto> categories), (override));
    MOCK_METHOD(void, setTag, (QList<TagDto> categories), (override));
    MOCK_METHOD(QWidget*, widget, (), (override));
    MOCK_METHOD(void, showErrorMessage, (const QString& message), (override));
    MOCK_METHOD(void, accept, (), (override));
};