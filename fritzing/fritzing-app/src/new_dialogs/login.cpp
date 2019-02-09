#include "login.h"
#include "ui_login.h"
#include "../Singleton.h"
#include <QCloseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    int w = this->geometry().width();
    int h = this->geometry().height();
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int w_all = screenRect.width();
    int h_all = screenRect.height();
    this->setGeometry(w_all/2-w/2,h_all/2-h/2,w,h);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    Singleton::GetInstance()->emitLogin(text);

    this->close();
}

void login::closeEvent(QCloseEvent *e){
    QString text = ui->lineEdit->text();
    if(text != ""){
        e->accept();
    }
    else{
        e->ignore();
        QMessageBox::warning(this,tr("warning"),tr("please input your name!"));
    }
}
