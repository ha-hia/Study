#include "SubRegisterView.h"
#include "ui_SubRegisterView.h"


SubRegisterView::SubRegisterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubRegisterView)
{
    ui->setupUi(this);
    setFixedSize(120, 120);
    //setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    /// 无边对话框
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    /// 窗口级别的模态
    setWindowModality(Qt::WindowModal);

    circleGif = new QMovie(":/imageSrc/Pic/circle2.gif");
    ui->circle->setMovie(circleGif);

    circleGif->start();
    ui->circle->setFixedSize(120, 120);

}

SubRegisterView::~SubRegisterView()
{
    delete circleGif;
    delete ui;
}
