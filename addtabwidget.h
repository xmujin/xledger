/**
 * @file addtabwidget.h
 * @author xiangxun (xiangxun76@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-04-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <QObject>
#include <QWidget>

class MyListView;
class MyButton;
class QAbstractItemModel;
class QLineEdit;
class AddTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddTabWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~AddTabWidget();

    void initUI();

    void setAddBtnText(const QString &text);

    void setModel(QAbstractItemModel *model);

    void setupConnections();

    QString getLineEditText() const;


signals:
    void addBtnClicked();
    void cancelBtnClicked();

private:
    MyListView *m_listView;
    MyButton *m_addBtn;
    MyButton *m_cancelBtn;
    QLineEdit *m_lineEdit;
};