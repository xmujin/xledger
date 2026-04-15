#pragma once
#include <QObject>


class CategoryModel;
class TagModel;
class AddCategoryTagView;
class AddCategoryTagPresenter: public QObject
{
    Q_OBJECT

public:
    explicit AddCategoryTagPresenter(CategoryModel *m_categoryModel, TagModel *m_tagModel, AddCategoryTagView *m_view, QObject *parent = nullptr);

signals:


private:
    CategoryModel *m_categoryModel;
    TagModel *m_tagModel;
    AddCategoryTagView *m_view;
};
