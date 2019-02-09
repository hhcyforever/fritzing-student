#include "dialog_additem.h"
#include "ui_dialog_additem.h"

dialog_additem::dialog_additem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_additem)
{
    ui->setupUi(this);
//    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
//    setAttribute(Qt::WA_TranslucentBackground);
}

dialog_additem::~dialog_additem()
{
    delete ui;
}

void dialog_additem::on_okButton_clicked()
{
    this->close();
}

void dialog_additem::on_introductonButton_clicked()
{

}
