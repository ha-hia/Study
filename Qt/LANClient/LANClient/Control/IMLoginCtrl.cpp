/*********************************************
File Name： IMLoginCtrl.cpp
Author：
Date：
Description： 用于控制登录的类
Changes：
********************************************/

#include "IMLoginCtrl.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QDataStream>
#include <QDateTime>
#include <QtNetwork>
#include <QInputDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

// public:-----------------------------------------------------------------
IMLoginCtrl::IMLoginCtrl(QObject *parent) :
    QObject(parent)
{
    m_tcpSocket = new IMTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(showConnectionStatus(QString, bool)),
            this, SLOT(changeLoginMessage(QString, bool)));

    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

IMLoginCtrl::~IMLoginCtrl()
{
}


/*************************************************
Function Name： login()
Description: 发送登录信息
Input： const QString &id： 用户帐号, const QString &pwd：用户密码
*************************************************/
void IMLoginCtrl::login(const QString &id, const QString &pwd, const int status)
{
    m_kind = LOGIN;
    m_loginInfo.m_userID = id;
    m_loginInfo.m_password = pwd;
    m_loginInfo. m_status = status;
    if (m_tcpSocket->isConnected())
    {
        requestLogin();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->ConnectToHost();
    }
}

/*************************************************
Function Name： getQuestionAndAnswer()
Description: 获取密保信息
*************************************************/
void IMLoginCtrl::getQuestionAndAnswer(const QString & id)
{
    m_kind = GET_QUESTION_ANSWER;
    m_loginInfo.m_userID = id;
    if (m_tcpSocket->isConnected())
    {
        requestGetQuestionAndAnswer();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->ConnectToHost();
    }
}

// mark: public slots:--------------------------------------------------------
/*************************************************
Function Name： changeLoginMessage()
Description: 改变登录信息
Input： const QString &mes： 信息, bool isLogin：状态
Output： nullptr
Changes： nullptr
*************************************************/
void IMLoginCtrl::changeLoginMessage(const QString &mes, bool isLogin)
{
    emit getLoginMessgae(mes, isLogin);
}

// mark: private slots:--------------------------------------------------

/*************************************************
Function Name： requestLogin()
Description: 请求登录
Input： nullptr
Output： nullptr
Changes： nullptr
*************************************************/
void IMLoginCtrl::requestLogin()
{
    if (nullptrptr == m_tcpSocket)
        return;

    QJsonObject json;
    json.insert("type",LOGIN);
    json.insert("userID", m_loginInfo.m_userID);
    json.insert("password", m_loginInfo.m_password);
    json.insert("status", ONLINE);

    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    m_tcpSocket->write(byte_array);
}



/*************************************************
Function Name： sendRequest()
Description: 发送请求
*************************************************/
void IMLoginCtrl::sendRequest()
{
    switch (m_kind)
    {
    case LOGIN:
    {
        requestLogin();
        break;
    }
    case GET_QUESTION_ANSWER:
    {
        requestGetQuestionAndAnswer();
        break;
    }
    default:
        break;
    }
}

// private slots:---------------------------------------------

/*************************************************
Function Name： requestGetQuestionAndAnswer()
Description: 发送获取密保问题以及答案的请求
*************************************************/
void IMLoginCtrl::requestGetQuestionAndAnswer()
{
    if (nullptrptr == m_tcpSocket)
        return;

    QJsonObject json;
    json.insert("type",GET_QUESTION_ANSWER);
    json.insert("userID", m_loginInfo.m_userID);
    json.insert("password", m_loginInfo.m_password);
    json.insert("status", ONLINE);

    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    m_tcpSocket->write(byte_array);
}

/*************************************************
Function Name： readMessage()
Description: 读取信息
Input： nullptr
Output： nullptr
Changes： nullptr
*************************************************/
void IMLoginCtrl::readMessage()
{



    QByteArray result= m_tcpSocket->readAll();
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(result, &json_error);
    QJsonObject json = document.object();

    int type = json.value("type").toInt();
    switch (type)
    {
    case LOGIN_SUCCESS:


        m_myself.m_regDateTime = json.value("registerDate").toString();
        m_myself.m_nickname = json.value("nickname").toString();
        json.value("gender");
        json.value("head");
        emit getLoginMessgae(tr("登录成功"), true, &m_myself);
        break;
    case LOGIN_FAIL:
        emit getLoginMessgae(tr("登录失败.帐号或者密码错误."),false);
        break;
    case HAVE_LOGINED:
        emit getLoginMessgae(tr("登录失败.该用户已经登录."),false);
        break;
//    case GET_QUESTION_ANSWER_FAIL:
//    {
//        QMessageBox::critical(nullptr, tr("找回密码"), tr("失败，帐号不存在！"));
//        break;
//    }
//    case GET_QUESTION_ANSWER_SUCCESS:
    {
        in >> m_tempStr;
        emit getQuestionAndAnswerSuccess(m_tempStr);

        while (1)
        {
            bool isOkMes = false;
            QString str = QString(tr("密保问题:%1\n请输入问题答案:"))
                    .arg(m_tempStr.m_two);
            QString answer = QInputDialog::getText(nullptr, "找回密码",
                                                   str,
                                                   QLineEdit::Normal,
                                                   nullptr,
                                                   &isOkMes);
            if (!isOkMes)
                break;
            if (answer != m_tempStr.m_three)
            {
                str = QString(tr("回答错误!"));
                QMessageBox::critical(nullptr, tr("找回密码"), str);
                continue;
            }
            else
            {
                str = QString(tr("回答正确!\n您的帐号是:%1\n您的密码是:%2"))
                        .arg(m_id)
                        .arg(IMEncryption::getInstace()
                             .getXorEncryptDecrypt(m_tempStr.m_one, 10));
                QMessageBox::information(nullptr, tr("找回密码"), str);
            }
            break;
        }
        break;

    }
    default:
        break;
    }

    QByteArray data = m_tcpSocket->readAll();
    qDebug() << "leaved in socket: " << data.size();
    m_blockSize = 0;
}

// mark: private----------------------------------------------------------

