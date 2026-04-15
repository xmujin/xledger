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
#include "tagdto.h"
#include <QObject>


class TagModel : public QObject {
  Q_OBJECT

public:
  explicit TagModel(QObject *parent = nullptr);

  bool addTag(const QString &tag);
  bool updateTag(int id, const QString &name);
  bool deleteTag(int id);

  QList<TagDto> getTags();

signals:
};
