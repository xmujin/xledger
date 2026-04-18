#pragma once
#include <QList>
struct TagDto;
class ITagModel
{
public:
	virtual bool addTag(const QString& tag) = 0;
	virtual bool updateTag(int id, const QString& name) = 0;
	virtual bool deleteTag(int id) = 0;
	virtual bool isExist(const QString& tag) = 0;
	virtual QList<TagDto> getTags() = 0;
};
