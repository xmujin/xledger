#pragma once

#include <QMainWindow>


class QSqlRelationalTableModel;
class MyComboBox;
class QDateEdit;
class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);



    void connectDb();

    void updateFilter();


    ~MainWindow();



private:
    QSqlRelationalTableModel *model;
    MyComboBox *balComboBox;
    MyComboBox *dateComboBox;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QLabel *lable;

};
