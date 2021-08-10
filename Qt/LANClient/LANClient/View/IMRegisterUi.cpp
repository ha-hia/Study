
#include "IMRegisterUi.h"
#include "ui_IMRegisterUi.h"

#include <QPalette>
#include <QMovie>
#include <QMessageBox>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

IMRegisterUi::IMRegisterUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IMRegisterUi)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("注册帐号"));
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(500, 390);

    registerCtrl = new IMRegisterCtrl(this);
    Q_ASSERT(nullptr != registerCtrl);

    InitWidget();
//    connect( registerCtrl, &IMRegisterCtrl::sigRegisterFailed, this, &IMRegisterUi::RegisterFailed);

    connect( registerCtrl, &IMRegisterCtrl::sigGetRegiterRet, this, &IMRegisterUi::ShowReturnInfo);
}

IMRegisterUi::~IMRegisterUi()
{
    delete ui;
    qDebug() << "IMRegisterUi destory" ;
}

/**
 * @brief 初始化注册界面
 */
void IMRegisterUi::InitWidget()
{
    /*******************************隐藏的注册中界面**************************************/
    registeringLabel = new QLabel;
    registeringLabel->setParent(this);
    registeringLabel->setFixedSize(120, 120);
    registeringLabel->move(210, 135);

    circleGif = new QMovie(":/imageSrc/Pic/circle2.gif");
    registeringLabel->setMovie(circleGif);
    circleGif->start();
    registeringLabel->hide();
    /*********************************************************************/
    ui->uiTitle->setText("注册用户信息");
    ui->nickName->setText(tr("*昵称"));
    ui->pwd->setText(tr("*密码"));
    ui->pwdInput->setPlaceholderText(tr("建议使用6-14位密码，不能包含空格"));
    ui->pwdInput->setEchoMode(QLineEdit::Password);
    ui->pwdInput->setMaxLength(14);

    ui->pwdConfirm->setText(tr("*确认密码"));
    ui->confirmPwdInput->setPlaceholderText(tr("请再次输入密码"));
    ui->confirmPwdInput->setEchoMode(QLineEdit::Password);
    ui->confirmPwdInput->setMaxLength(14);

    ui->gender->setText(tr("性别"));
    ui->genderBox->addItem(tr("男"));
    ui->genderBox->addItem(tr("女"));
    ui->question->setText(tr("密保问题"));
    ui->questionInput->setPlaceholderText(tr("用于找回密码的令牌"));
    ui->answer->setText(tr("密保答案"));
    ui->answerInput->setPlaceholderText(tr("一定记住！"));
    ui->registerBtn->setText(tr("注册"));
    ui->cancelBtn->setText(tr("取消"));
}

/**
 * @brief 点击取消按钮，关闭注册界面
 */
void IMRegisterUi::on_cancelBtn_clicked()
{
    this->close();
}
/**
 * @brief 点击注册按钮，连接服务器，开始注册
 */
void IMRegisterUi::on_registerBtn_clicked()
{
    ui->pwdInput->setReadOnly(true);
    ui->answerInput->setReadOnly(true);
    ui->nickNameInput->setReadOnly(true);
    ui->questionInput->setReadOnly(true);
    ui->confirmPwdInput->setReadOnly(true);

    // 判断昵称是否为空
    if (ui->nickNameInput->text().isEmpty())
    {
        QMessageBox::about(this, tr("提示"), tr("昵称不能为空"));
        return;
    }
    // 判断密码是否为空
    if (ui->pwdInput->text().isEmpty())
    {
        QMessageBox::about(this, tr("提示"), tr("密码不能为空"));
        return;
    }
    // 判断密码是否符合要求
    if (ui->pwdInput->text().length()>14 || ui->pwdInput->text().length()<6)
    {
        QMessageBox::about(this, tr("提示"), tr("密码长度不符合"));
        return;
    }
    // 判断确认密码是否为空
    if (ui->confirmPwdInput->text().isEmpty())
    {
        QMessageBox::about(this, tr("提示"), tr("请确认密码"));
        return;
    }
    // 判断密码是否一致
    if (ui->pwdInput->text().compare(ui->confirmPwdInput->text()) != 0)
    {
        QMessageBox::about(this, tr("提示"), tr("密码不一致"));
        return;
    }
    // 判断密保问题是否为空
    if (ui->questionInput->text().isEmpty())
    {
        QMessageBox::about(this, tr("提示"), tr("密保不能为空"));
        return;
    }
    // 判断问题答案是否为空
    if (ui->answerInput->text().isEmpty())
    {
        QMessageBox::about(this, tr("提示"), tr("问题答案不能为空"));
        return;
    }

    /*************保存信息到结构体，后续需要改善为JSON格式*********************/
    m_userInf.m_nickname = ui->nickNameInput->text();
    m_userInf.m_password = ui->pwdInput->text();
    m_userInf.m_question = ui->questionInput->text();
    m_userInf.m_answer = ui->answerInput->text();
    m_userInf.m_gender = ui->genderBox->currentText();

    if(nullptr == registerCtrl)
    {
        registerCtrl = new IMRegisterCtrl;
        Q_ASSERT(nullptr != registerCtrl);
    }

    registeringLabel->show();
    registerCtrl->RegisterID(m_userInf);

}

//void IMRegisterUi::RegisterFailed()
//{
//    this->close();
//}

void IMRegisterUi::ShowReturnInfo(QString& res)
{
    this->close();
    if(res.isEmpty())
    {
        return;
    }
    QMessageBox::about(this, tr("提示"), res);
}
