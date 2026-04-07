#pragma once

#include <QWidget>
class QLabel;
class MyButton;
class QPropertyAnimation;
class MyListWidgetItem: public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor bgColor READ bgColor WRITE setBgColor NOTIFY bgColorChanged)

public:
    explicit MyListWidgetItem(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    inline QColor bgColor() const { return m_bgColor; };
    void setBgColor(const QColor &color);

    void setLabelText(const QString& str);

signals:
    void btnClicked();
    void bgColorChanged(const QColor &color);
    
protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

public:
    QLabel *label;
    MyButton *btn;
    QPropertyAnimation *m_bgAnim; 
    QColor m_normalColor{Qt::white}; // 默认背景颜色
    QColor m_hoverColor{"#266FFF"}; // 默认背景颜色
    QColor m_bgColor{Qt::white}; // 默认背景颜色
};
