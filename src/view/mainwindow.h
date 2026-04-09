#pragma once

#include <QMainWindow>


class QSqlRelationalTableModel;
class MyComboBox;
class QComboBox;
class QDateEdit;
class QLabel;
class QHBoxLayout;
class QTableView;
class MyButton;
class MySqlRelationalTableModel;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);



    void initBase();
    void connectDb();
    void createMenu();

    void createMainLayout();
    void createHBoxLayout();
    void createTableView();

    void setupConnections();

    ~MainWindow();
    

private slots:
    void updateFilter();

private:
    MySqlRelationalTableModel *model;
    QComboBox *balComboBox;
    MyComboBox *dateComboBox;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QLabel *lable;
    QHBoxLayout *hBoxLayout;
    QTableView *tableView;
    MyButton *addBtn;

    Ui::MainWindow *ui;
};
