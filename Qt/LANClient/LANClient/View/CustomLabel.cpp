#include "CustomLabel.h"
#include <QMouseEvent>

CustomLabel::CustomLabel(QWidget *parent) : QLabel(parent)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::darkGreen);
    setPalette(pa);
}

CustomLabel::CustomLabel(const QString& text, QWidget *parent) : QLabel(parent)
{
    this->setText(text);
}

CustomLabel::~CustomLabel()
{

}

void CustomLabel::mousePressEvent(QMouseEvent *ev)
{
    if(Qt::LeftButton == ev->button())
    {
        emit clicked();
    }
}

void CustomLabel::enterEvent(QEvent *event)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::green);
    setPalette(pa);
}

void CustomLabel::leaveEvent(QEvent *event)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::black);
    setPalette(pa);
}
