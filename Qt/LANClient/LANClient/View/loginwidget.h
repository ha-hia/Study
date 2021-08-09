#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "IMMainWidget.h"
#include "Control/IMMainCtrl.h"
#include "Control/IMConstant.h"
//#include "Control/IMLoginCtrl.h"
#include "View/IMRegisterUi.h"
#include "CustomLabel.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QPoint>
#include <QPropertyAnimation>


class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    //界面布局
    void init();
    //登陆时界面变化
    void RegisterUiChange(bool input);

public slots:
    void showExtend(bool pram);
    void ClickLogin(bool pram);
    void ClickClose();
    void ClickRegister();
    void HandleLogin(const QString & strRet, bool isLogin = false, UserInfor * me = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief 根据拓展界面的服务器参数设置IP和PORT，或默认
    */
    void setServer(const QString &ip = "120.79.139.92", const quint16 port = 6666);

private:
    IMMainWidget* m_mainWidget;
    IMMainCtrl* m_mainctl;
    QWidget* toolWidget;
    QPushButton* m_setBtn;
    CustomLabel* m_closeLab;
    QLabel* m_showGif;
    QLabel* m_showHead;
    QLineEdit* m_IDLine;
    QLineEdit* m_pwdLine;
    CustomLabel* m_register;
    CustomLabel* m_forgetPwd;
    QPushButton* m_loginBtn;
    QWidget* m_extendWidget;
    QLineEdit* m_serverIP;
    QLineEdit* m_serverPort;
    QPoint m_tempPoint;
    QPoint m_SrcPoint;
    QPropertyAnimation* logining;

    bool isLogin;
    IMRegisterUi* registerUi;   /// 注册界面
//    IMLoginCtrl* m_loginCtrl;   /// 用于控制登录
};

#endif // LOGINWIDGET_H
