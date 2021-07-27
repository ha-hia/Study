
#include "loginwidget.h"
#include "Control/IMTcpSocket.h"

#include <QString>
#include <QMovie>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent), isLogin(false)
{
    init();
    connect(this->m_setBtn, &QPushButton::toggled, this, &LoginWidget::showExtend);
    connect(this->m_closeLab, &CustomLabel::clicked, this, &LoginWidget::ClickClose);
    connect(this->m_register, &CustomLabel::clicked, this, &LoginWidget::ClickRegister);
    connect(this->m_loginBtn, &QPushButton::toggled, this, &LoginWidget::ClickLogin);
    connect(m_loginCtrl, &IMLoginCtrl::getLoginMessgae, this, &LoginWidget::HandleLogin);
}

LoginWidget::~LoginWidget()
{

}

void LoginWidget::init()
{
    setFixedSize(400,350);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    m_loginCtrl = new IMLoginCtrl(this);
    /***********************开始界面布局*****************************************/
    /***********************top*****************************************/
    m_closeLab = new CustomLabel;
    m_closeLab->setText("X");
    m_closeLab->setFixedSize(20, 20);

    m_setBtn = new QPushButton;
    m_setBtn->setIcon( QPixmap(":/imageSrc/Pic/setting.png") );
    m_setBtn->setCheckable(true);
    m_setBtn->setAutoDefault(false);
    m_setBtn->setStyleSheet("border:none;");//m_setBtn->setFlat(true);
    m_setBtn->setFixedSize(20, 20);

    QHBoxLayout* top= new QHBoxLayout;
    top->addWidget(m_setBtn, 0, Qt::AlignLeft);
    top->addWidget(m_closeLab, 0, Qt::AlignRight);

    m_showGif = new QLabel;
    QMovie *loginGif = new QMovie(":/imageSrc/Pic/loginShow.gif");
    m_showGif->setMovie(loginGif);
    loginGif->start();
    m_showGif->setFixedSize(400,150);

    /***********************mid*****************************************/
    m_showHead = new QLabel;//显示QQ头像
    m_showHead->setPixmap( QPixmap(":/imageSrc/Pic/head.jpg") );
    QVBoxLayout* midLeft = new QVBoxLayout;
    midLeft->addWidget(m_showHead);

    logining = new QPropertyAnimation(m_showHead, "geometry");

    m_IDLine = new QLineEdit;
    m_IDLine->setPlaceholderText(tr("账号"));
    m_register = new CustomLabel(tr("注册账号"));
    QHBoxLayout* midTop = new QHBoxLayout;
    midTop->addWidget(m_IDLine);
    midTop->addWidget(m_register);

    m_pwdLine = new QLineEdit;
    m_pwdLine->setPlaceholderText(tr("密码"));
    m_pwdLine->setEchoMode(QLineEdit::Password);
    m_forgetPwd  = new CustomLabel(tr("忘记密码"));
    QHBoxLayout* midBottom = new QHBoxLayout;
    midBottom->addWidget(m_pwdLine);
    midBottom->addWidget(m_forgetPwd);
    QVBoxLayout* midCentral = new QVBoxLayout;
    midCentral->addLayout(midTop);
    midCentral->addLayout(midBottom);

    QHBoxLayout* mid = new QHBoxLayout;
    mid->addLayout(midLeft);
    mid->addLayout(midCentral);

    /***********************bottom*****************************************/
    m_loginBtn = new QPushButton(tr("登陆"));
    m_loginBtn->setStyleSheet("background-color:rgb(231,0,132);color:white;border-radius:2px");
    m_loginBtn->setFixedSize(100, 40);
    m_loginBtn->setCheckable(true);
    m_loginBtn->setAutoDefault(false);

    /***********************extend default is hide*****************************************/
    m_serverIP = new QLineEdit;;
    m_serverIP->setPlaceholderText(tr("服务器IP地址"));
    m_serverPort = new QLineEdit;
    m_serverPort->setFixedWidth(60);
    m_serverPort->setPlaceholderText(tr("端口号"));

    m_extendWidget = new QWidget;
    QHBoxLayout* extended= new QHBoxLayout;
    extended->setMargin(0);
    extended->addWidget(m_serverIP);
    extended->addWidget(m_serverPort);
    m_extendWidget->setLayout(extended);
    m_extendWidget->setParent(this);

    /***********************main*****************************************/

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(top);
    mainLayout->addWidget(m_showGif);
    mainLayout->addLayout(mid);
    mainLayout->addWidget(m_loginBtn, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_extendWidget);
    mainLayout->setMargin(5);

    setLayout(mainLayout);
    m_extendWidget->hide();
}

void LoginWidget::RegisterUiChange(bool input)
{
    /// 登陆中...转圈圈
    if(true == input)
    {
        m_loginBtn->setText(tr("取消"));
        m_setBtn->hide();
        m_closeLab->show();
        m_IDLine->hide();
        m_pwdLine->hide();
        m_register->hide();
        m_forgetPwd->hide();
        m_extendWidget->hide();
        logining->setDuration(400);
        logining->setStartValue(QRect(30, 190, 105, 105));
        logining->setEndValue(QRect(150, 190, 105, 105));
        logining->start();
    }
    /// 取消登陆
    else
    {
        m_loginCtrl->AbortConnect();
        m_loginBtn->setText(tr("登陆"));
        m_setBtn->show();
        m_IDLine->show();
        m_pwdLine->show();
        m_register->show();
        m_forgetPwd->show();
        m_extendWidget->hide();
    }
}

void LoginWidget::showExtend(bool pram)
{
    if(pram)
        qDebug() << "true";
    else
        qDebug() << "false";
    if(true == pram)
    {
        m_extendWidget->show();
    }
    else
    {
        m_extendWidget->hide();
    }
}

void LoginWidget::ClickRegister()
{
    setServer();
    registerUi = new IMRegisterUi();
    registerUi->show();
}

void LoginWidget::ClickLogin(bool pram)
{
    setServer();
    if(pram == true)
    {
        QString ID = m_IDLine->text();
        QString pwd = m_pwdLine->text();
        if(ID.isEmpty() || pwd.isEmpty())
        {
            QMessageBox::critical(this, "错误", "账号或密码不能为空！");
            return;
        }
        RegisterUiChange(true);
        /// 向登录控制类传递登录数据，具体的请求在控制类里处理，待实现
        if (m_loginCtrl == nullptr)
        {
            m_loginCtrl = new IMLoginCtrl(this);
        }
        m_loginCtrl->login(ID, pwd);

    }
    else
    {
        /// 断开连接
        //m_loginCtrl->AbortConnect();
        RegisterUiChange(false);
        isLogin = false;
    }
}

void LoginWidget::ClickClose()
{
    this->close();
}

void LoginWidget::setServer(const QString &ip, const quint16 port)
{
    QString tempAddr;
    quint16 tempPort;
    if(m_serverIP->text().isEmpty())
    {
        tempAddr = ip;
    }
    else {
        tempAddr = m_serverIP->text();
    }

    if(m_serverPort->text().isEmpty())
    {
        tempPort = port;
    }
    else {
        tempPort = m_serverPort->text().toUShort();
    }

    IMTcpSocket::m_hostAddress = QHostAddress(tempAddr);
    IMTcpSocket::m_hostPort = tempPort;
}

void LoginWidget::HandleLogin(const QString & strRet, bool isLogin, const UserInfor* loginInfo)
{
    /// 成功登陆
    if (isLogin == true)
    {
        /// 关闭登陆界面
        this->close();

        /// 显示主界面

    }
    /// 避免反复提示
    else if( strRet.contains("neterror") )
    {
        RegisterUiChange(false);
    }
    else
    {
        QMessageBox::about( this, tr("提示"), strRet );
        /// 切回输入账号密码界面
        RegisterUiChange(false);
    }
}

void LoginWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_tempPoint = event->globalPos() - this->frameGeometry().topLeft();
    }
    else
    {
        return mousePressEvent(event);
    }
}

void LoginWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        move(event->globalPos() - m_tempPoint);
    }
    else
    {
        return mousePressEvent(event);
    }
}
