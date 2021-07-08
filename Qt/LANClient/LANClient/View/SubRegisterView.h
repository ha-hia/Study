#ifndef SUBREGISTERVIEW_H
#define SUBREGISTERVIEW_H

#include <QWidget>
#include <QMovie>

namespace Ui {
class SubRegisterView;
}

class SubRegisterView : public QWidget
{
    Q_OBJECT

public:
    explicit SubRegisterView(QWidget *parent = nullptr);
    ~SubRegisterView();

private:
    Ui::SubRegisterView *ui;
    QMovie *circleGif;
};

#endif // SUBREGISTERVIEW_H
