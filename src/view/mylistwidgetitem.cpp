#include "mylistwidgetitem.h"
#include <QHBoxLayout>
#include <QLabel>
#include "mybutton.h"
#include <QFont>
#include <QPainter>
#include <QPropertyAnimation>


MyListWidgetItem::MyListWidgetItem(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
    , m_bgAnim{new QPropertyAnimation(this, "bgColor", this)}
{
   
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    label = new QLabel("我是占位符号 啦啦啦");
    QFont font = label->font();
    font.setPointSize(13);
    label->setFont(font);


    btn = new MyButton("删除");
    btn->setFixedSize(60, 30);
    //  设置按钮样式

    btn->setBgColor(QColor("#FF4D4D"));
    btn->setButtonColors(
        QColor("#FF4D4D"),  // 正常
        QColor("#FF6666"), 
        QColor("#CC0000"));


    mainLayout->addWidget(label);
    mainLayout->addStretch();
    mainLayout->addWidget(btn);


    // 发送信号
    connect(btn, &MyButton::clicked, this, [=] {
        emit btnClicked();
    });


}

void MyListWidgetItem::setBgColor(const QColor &color)
{
    if (color != m_bgColor) {
        m_bgColor = color;
        update(); // 触发重绘
        emit bgColorChanged(color);
    }
}

void MyListWidgetItem::setLabelText(const QString &str)
{
    label->setText(str);
}

void MyListWidgetItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor textColor = palette().color(QPalette::ButtonText);


    // 开启抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 绘制按钮背景
    painter.setPen(Qt::NoPen);     
    painter.setBrush(m_bgColor);
    painter.drawRect(rect()); 
}

void MyListWidgetItem::enterEvent(QEnterEvent *event)
{
    m_bgAnim->stop();
    m_bgAnim->setDuration(200);
    m_bgAnim->setStartValue(m_normalColor);
    m_bgAnim->setEndValue(m_hoverColor);
    m_bgAnim->start();
    QWidget::enterEvent(event);

}

void MyListWidgetItem::leaveEvent(QEvent *event)
{
    m_bgAnim->stop();
    m_bgAnim->setDuration(200);
    m_bgAnim->setStartValue(m_hoverColor);
    m_bgAnim->setEndValue(m_normalColor);
    m_bgAnim->start();
    QWidget::leaveEvent(event);
}
