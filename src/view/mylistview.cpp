#include "mylistview.h"
#include <QStringListModel>


MyListView::MyListView(QWidget *parent)
{
    setFixedHeight(350);


    QStringListModel *model = new QStringListModel;
    QStringList list;
    list << "a" << "b" << "c";
    model->setStringList(list);
    setModel(model);


}

MyListView::~MyListView()
{
}
