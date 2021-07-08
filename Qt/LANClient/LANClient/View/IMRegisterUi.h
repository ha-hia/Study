
/**
 * @file IMRegisterUi.h
 * @brief 注册界面类
 */


#ifndef IMREGISTERUI_H
#define IMREGISTERUI_H

#include "SubRegisterView.h"
#include "Control/IMRegisterCtrl.h"
#include "Control/IMConstant.h"
#include <QWidget>
#include <QLabel>
#include <QSharedPointer>

namespace Ui {
class IMRegisterUi;
}

class IMRegisterUi : public QWidget
{
    Q_OBJECT

public:
    explicit IMRegisterUi(QWidget *parent = nullptr);
    ~IMRegisterUi();

    /**
     * @brief 初始化注册界面
     */
    void InitWidget();
private slots:

    /**
     * @brief 点击取消按钮，关闭注册界面
     */
    void on_cancelBtn_clicked();
    /**
     * @brief 点击注册按钮，连接服务器，开始注册
     */
    void on_registerBtn_clicked();

private:
    /**
     * @brief 注册错误/成功时，显示注册界面
     */
    void ShowRegisterAgain();

private:
    Ui::IMRegisterUi *ui;
    UserInfor m_userInf;

    SubRegisterView subView;
    IMRegisterCtrl* registerCtrl;

};

#endif // IMREGISTERUI_H
