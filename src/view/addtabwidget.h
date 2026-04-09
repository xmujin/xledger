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

class QListWidget;
class MyButton;
class QAbstractItemModel;
class QLineEdit;
class AddTabWidget : public QWidget
{
    Q_OBJECT
public:

    enum TabType { Category, Tag };

    explicit AddTabWidget(TabType t, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~AddTabWidget();

    void initUI();

    void setAddBtnText(const QString &text);


    void setupConnections();

    QString getLineEditText() const;


    void addListWidgetItem(const QString&str);


signals:
    void addBtnClicked();
    void cancelBtnClicked();

private:
    TabType m_type;
    QListWidget *m_listWidget;
    MyButton *m_addBtn;
    MyButton *m_cancelBtn;
    QLineEdit *m_lineEdit;
};