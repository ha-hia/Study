
#include "Control/IMTcpSocket.h"
#include "IMRegisterCtrl.h"


IMRegisterCtrl::IMRegisterCtrl(QObject *parent) : QObject(parent)
{

}
/**
 * @brief 根据输入的 input 信息，向服务器注册账号
 */
void IMRegisterCtrl::RegisterID(UserInfor *input)
{
    IMTcpSocket* registerSocket = IMTcpSocket::GetInstance();
    if(registerSocket->isConnected());
}
