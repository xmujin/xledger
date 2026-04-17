#pragma once
#include <QList>
#include "categorydto.h"
#include "tagdto.h"


class IAddView
{
public:
	virtual void setCategory(QList<CategoryDto> categories) = 0;
	virtual void setTag(QList<TagDto> tags) = 0;
};