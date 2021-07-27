
/*****************测试加入******************************************/
#include "View/IMMainWidget.h"
#include "Control/IMConstant.h"
/*****************测试加入******************************************/

#include "View/loginwidget.h"
#include "View/CustomLabel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

//   测试注释
//   LoginWidget w;
//   w.show();

/*****************测试加入******************************************/
    UserInfor me;
    me.m_gender = "男";
    me.m_nickname = "大帅";
    me.m_status = 5;
    me.m_userID = "12346578";
    me.m_headPortrait = 2;

    IMMainWidget *mainWidget = new IMMainWidget(me);
    mainWidget->getFriendsInformation();
    mainWidget->show();
/*****************测试加入******************************************/
   return a.exec();
}
