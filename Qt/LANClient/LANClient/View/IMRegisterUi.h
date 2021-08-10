
/**
 * @file IMRegisterUi.h
 * @brief 注册界面类
 */


#ifndef IMREGISTERUI_H
#define IMREGISTERUI_H

#include "Control/IMRegisterCtrl.h"
#include "Control/IMConstant.h"
#include <QWidget>
#include <QLabel>
#include <QSharedPointer>
#include <QMovie>
#include <QDebug>

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
//    void RegisterFailed();
    void ShowReturnInfo(QString& res);

private:
    Ui::IMRegisterUi *ui;
    UserInfor m_userInf;
    /// 注册逻辑类
    IMRegisterCtrl* registerCtrl;

    QLabel *registeringLabel;
    QMovie* circleGif;
};

#endif // IMREGISTERUI_H
