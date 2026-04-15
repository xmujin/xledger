#pragma once

#include <QObject>
#include <QDialog>
#include <qcontainerfwd.h>
#include "billdto.h"


namespace Ui {
    class AddBillView;
}

struct BillDto;
struct TagDto;
struct CategoryDto;
class AddBillView: public QDialog
{
    Q_OBJECT

public:
    explicit AddBillView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void setCategory(QList<CategoryDto> categories);
    void setTag(QList<TagDto> tags);

signals:
    void addBillClicked(BillDto billDto);
public slots:
    void onSubmit();
private:
    Ui::AddBillView *ui;   
};
