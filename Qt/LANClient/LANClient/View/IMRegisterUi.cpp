#include "IMRegisterUi.h"
#include "ui_IMRegisterUi.h"
#include <QPalette>
#include <QMessageBox>

IMRegisterUi::IMRegisterUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IMRegisterUi)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("注册IM帐号"));
    this->setFixedSize(500, 390);
    init();
}

IMRegisterUi::~IMRegisterUi()
{
    delete ui;
}

void IMRegisterUi::init()
{
    ui->uiTitle->setText("注册用户信息");
//    QPalette pa;
//    pa.setColor(QPalette::WindowText, Qt::black);
//    ui->uiTitle->setPalette(pa);
//    QFont ft;
//    ft.setPointSize(15);
//    ui->uiTitle->setFont(ft);

    ui->nickName->setText(tr("*昵称"));
    ui->pwd->setText(tr("*密码"));
    ui->pwdInput->setPlaceholderText(tr("建议使用6-14位密码，不能包含空格"));
    ui->pwdInput->setEchoMode(QLineEdit::Password);
    ui->pwdInput->setMaxLength(14);

    ui->pwdConfirm->setText(tr("*确认密码"));
    ui->pwdInput->setPlaceholderText(tr("请再次输入密码"));
    ui->pwdInput->setEchoMode(QLineEdit::Password);
    ui->pwdInput->setMaxLength(14);
    ui->gender->setText(tr("性别"));
    ui->genderBox->addItem(tr("男"));
    ui->genderBox->addItem(tr("女"));
    ui->question->setText(tr("密保问题"));
    ui->questionInput->setPlaceholderText(tr("用于找回密码的令牌"));
    ui->answer->setText(tr("密保答案"));
    ui->answerInput->setPlaceholderText(tr("一定记住！"));
    ui->registerBtn->setText(tr("注册"));
    ui->cancelBtn->setText(tr("取消"));
    //ui->gridLayout->setFixedSize(500, 390);
}

/**
 * @brief 点击取消按钮
*/
void IMRegisterUi::on_cancelBtn_clicked()
{
    this->close();
}
/**
 * @brief 单击注册按钮
*/
void IMRegisterUi::on_registerBtn_clicked()
{
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


}
