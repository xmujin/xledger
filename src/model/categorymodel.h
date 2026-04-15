#pragma once
#include <QObject>
#include "categorydto.h"

struct CategoryDto;
class CategoryModel: public QObject
{
    Q_OBJECT

public:
    explicit CategoryModel(QObject *parent = nullptr);

    QList<CategoryDto> getCategories();

    bool addCategory(const QString &category);
    bool updateCategory(int id, const QString &name);
    bool deleteCategory(int id);


    signals:
};
