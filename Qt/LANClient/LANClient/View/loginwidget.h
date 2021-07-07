#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

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
    LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    //界面布局
    void init();
    //登陆时界面变化
    void UiChangeShow(bool input);


public slots:
    void showExtend(bool pram);
    void ClickLogin(bool pram);
    void ClickClose();
    void ClickRegister();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief 根据拓展界面的服务器参数设置IP和PORT，或默认
    */
    void setServer(const QString &ip = "120.79.139.92", const quint16 port = 6666);

private:
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
    IMRegisterUi* registerUi;
};

#endif // LOGINWIDGET_H
