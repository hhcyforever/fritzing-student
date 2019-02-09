#include "highlight.h"
#include "ui_highlight.h"

highlight::highlight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::highlight)
{
    ui->setupUi(this);
}

highlight::~highlight()
{
    delete ui;
}
