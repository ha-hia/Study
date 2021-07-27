#ifndef IMINFORMATIONWIDGET_H
#define IMINFORMATIONWIDGET_H

#include <QWidget>
#include "Control/IMConstant.h"

class QPushButton;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QFrame;
class IMMainWidget;

static const int MAX_NUM = 133;			//总头像数

class IMInformationWidget : public QWidget
{
    Q_OBJECT
public:
    IMInformationWidget(IMMainWidget *mainWidget, QWidget *parent = nullptr);
     ~IMInformationWidget();

    void setReadOnly(bool isReadOnly, bool isEdit);
//    void setWrite();
    void setUserInfor(const UserInfor &user);
    UserInfor getInformation();
protected:
    void closeEvent(QCloseEvent *);
signals:
//    void sendInformation(const UserInfor &user);
public slots:
    void onClickCancelButton();
    void onClickOKButton();
    void onClickPretButton();
    void onClickNextButton();

private:
    void initLoginWidget();

protected:
    QLabel *m_labelUserID;    // 用户帐号
    QLineEdit *m_leUserID;
//     QLabel *m_labelDesUserID;
    QLabel *m_labelNickname;   // 用户昵称
    QLineEdit *m_leNickname;

    QFrame *m_frameHead;
    QLabel *m_labelHead;
//    QLabel *m_labelHeadMes;
    QPushButton *m_btnNext;
    QPushButton *m_btnPre;
//        QLabel *m_labelDesNickname;// 昵称描述
//        QLabel *m_labelPwd;        // 用户密码
//        QLineEdit *m_lePwd;
//        QLabel *m_labelDesPwd;
        QLabel *m_labelConfirmPwd;  // 确认密码
        QLineEdit *m_leConfirmPwd;
//        QLabel *m_labelDesConfirmPwd;
        QLabel *m_labelSex;        // 性别
        QComboBox *m_cbxSex;
//        QLabel *m_labelDesSex;

//        QLabel *m_labelDesBirthday;
//        QLabel *m_labelQuestion;   // 密保问题
//        QLineEdit *m_leQuestion;
//        QLabel *m_labelDesQuestion;
//        QLabel *m_labelAnswer;     // 问题答案
//        QLineEdit *m_leAnswer;
//        QLabel *m_labelDesAnswer;


        QPushButton *m_btnOk;// "注册" 按钮
        QPushButton *m_btnCancel;  // "取消" 按钮

        int m_headNum;
        bool m_isReadOnly;
        bool m_isEdit;

        UserInfor m_userInf;
        IMMainWidget *m_mainWidget;
};

#endif // IMINFORMATIONWIDGET_H
