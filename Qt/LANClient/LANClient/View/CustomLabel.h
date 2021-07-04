#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    CustomLabel(QWidget* parent = nullptr);
    CustomLabel(const QString& text, QWidget* parent = nullptr);
    ~CustomLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *ev);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // CUSTOMLABEL_H
