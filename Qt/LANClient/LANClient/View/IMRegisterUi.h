#ifndef IMREGISTERUI_H
#define IMREGISTERUI_H

#include "Control/IMConstant.h"
#include <QWidget>

namespace Ui {
class IMRegisterUi;
}

class IMRegisterUi : public QWidget
{
    Q_OBJECT

public:
    explicit IMRegisterUi(QWidget *parent = nullptr);
    ~IMRegisterUi();
    void init();
private slots:
    void on_cancelBtn_clicked();

    void on_registerBtn_clicked();

private:
    Ui::IMRegisterUi *ui;
    UserInfor m_userInf;
};

#endif // IMREGISTERUI_H
