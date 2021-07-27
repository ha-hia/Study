
#include "Control/IMTcpSocket.h"
#include "IMRegisterCtrl.h"

#include <QAbstractSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>


IMRegisterCtrl::IMRegisterCtrl(QObject *parent)
    : QObject(parent)
{
    registerSocket = new IMTcpSocket(this);

    /// 成功连接，则向服务器发送注册请求
    connect(this->registerSocket, &IMTcpSocket::connected, this, &IMRegisterCtrl::RegisterRequest);

    /// 当连接出现错误，则再次显示注册界面
    void(QAbstractSocket::*ptr)(QAbstractSocket::SocketError) = &QAbstractSocket::error;
//    connect(this->registerSocket, ptr, this, &IMRegisterCtrl::RegisterFailed);
    connect(this->registerSocket, ptr, this, &IMRegisterCtrl::RegisterResult);

    /// 接收到回复消息
    connect(this->registerSocket, &IMTcpSocket::readyRead, this, &IMRegisterCtrl::RegisterResult);

}

IMRegisterCtrl::~IMRegisterCtrl()
{
}
/**
 * @brief 根据输入的 input 信息，向服务器注册账号 m
 */
void IMRegisterCtrl::RegisterID(UserInfor& input)
{
    m_userInfo = input;

    if(false == registerSocket->isConnected())
    {
        registerSocket->ConnectToHost();
    }
    else {
        RegisterRequest();
    }
}
/**
 * @brief 请求服务器注册
 */
void IMRegisterCtrl::RegisterRequest()
{
    QJsonObject json;
    json.insert("type",REGISTER);
    json.insert("nikeName", m_userInfo.m_nickname);
    json.insert("password", m_userInfo.m_password);
    json.insert("gender", m_userInfo.m_gender);
    json.insert("question", m_userInfo.m_question);
    json.insert("answer", m_userInfo.m_answer);
    /// 离线状态
    json.insert("status", 1);
    /// 初始头像
    json.insert("headPortrait", 1);

    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);

    registerSocket->write(byte_array);
    qDebug() << "send: " << byte_array;
}

/**
 * 对应21行,优化至95-99行
 */
void IMRegisterCtrl::RegisterFailed()
{
    emit sigRegisterFailed();
}

void IMRegisterCtrl::RegisterResult()
{
    QByteArray result= registerSocket->readAll();
    if(result.size() == 0)
    {
        QString strRet = "";
        emit sigGetRegiterRet(strRet);
    }

    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(result, &json_error);
    QJsonObject json = document.object();

    int type = json.value("type").toString().toInt();
    switch (type) {
        case REGISTER_FAILED:
        {
            QString strRet(tr("客官不好意思,该昵称已注册!\n请再次注册！"));
            emit sigGetRegiterRet(strRet);
            break;
        }
        case REGISTER_SUCCESS:
        {
            QString strUserID = json.value("userID").toString();
            QString strRet(tr("恭喜客官,注册成功！\n登录ID: "));
            strRet += strUserID;
            emit sigGetRegiterRet(strRet);
            break;
        }
        default:
        {
            QString strRet(tr("未知错误"));
            emit sigGetRegiterRet(strRet);
            break;
        }
    }

}


