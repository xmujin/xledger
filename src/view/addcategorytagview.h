/**
 * @file addcategorytagview.h
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:28 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include <QDialog>
#include "categorydto.h"
#include "tagdto.h"
#include "addcategorytagview.h"
#include "iaddview.h"

namespace Ui {
    class AddCategoryTagView;
}

struct CategoryDto;
struct TagDto;
class QStandardItemModel;
class AddCategoryTagView: public QDialog, public IAddView
{
    Q_OBJECT

public:
    enum UserData {
		IdRole = Qt::UserRole + 1,
		BackUpRole
    };


    explicit AddCategoryTagView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void setCategory(QList<CategoryDto> categories) override;
    void setTag(QList<TagDto> tags) override;
    QWidget* widget() override { return this; }



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
