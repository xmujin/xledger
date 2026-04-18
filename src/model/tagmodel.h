/**
 * @file tagmodel.h
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:91 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include "itagmodel.h"
#include "tagdto.h"
#include <QObject>


class TagModel : public QObject, public ITagModel
{
  Q_OBJECT

public:
	explicit TagModel(QObject *parent = nullptr);

	bool addTag(const QString &tag) override;
	bool updateTag(int id, const QString &name) override;
	bool deleteTag(int id) override;
	bool isExist(const QString& tag) override;
	QList<TagDto> getTags() override;
signals:
};
