#pragma once

#include <QDialog>
#include "categorydto.h"
#include "tagdto.h"

namespace Ui {
    class AddCategoryTagView;
}

struct CategoryDto;
struct TagDto;
class QStandardItemModel;
class AddCategoryTagView: public QDialog
{
    Q_OBJECT

public:
    explicit AddCategoryTagView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());


    void setCategory(QList<CategoryDto> categories);
    void setTag(QList<TagDto> tags);

signals:
    void addCategoryRequest(const QString &category);
    void addTagRequest(const QString &tag);
    void updateCategoryRequest(int id, const QString &name);
    void updateTagRequest(int id, const QString &name);
    void deleteCategoryRequest(int id);
    void deleteTagRequest(int id);
    

private:
    Ui::AddCategoryTagView *ui;
    QStandardItemModel *m_categoryModel; 
    QStandardItemModel *m_tagModel;
};
