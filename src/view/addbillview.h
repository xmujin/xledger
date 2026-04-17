/**
 * @file addbillview.h
 * @author xiangxun
 * @brief 
 * @date 2026-04-15 20:04:18 
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
#include <QObject>
#include <QDialog>
#include <QList>
#include "billdto.h"
#include "addbillview.h"
#include "iaddview.h"

namespace Ui {
    class AddBillView;
}
struct BillDto;
struct TagDto;
struct CategoryDto;
class AddBillView : public QDialog, public IAddView
{
    Q_OBJECT

public:
    explicit AddBillView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void setCategory(QList<CategoryDto> categories) override;
    void setTag(QList<TagDto> tags) override;

public slots:
    void onSubmit();

signals:
    void addBillClicked(BillDto dto);
private:
    Ui::AddBillView *ui;   
};
