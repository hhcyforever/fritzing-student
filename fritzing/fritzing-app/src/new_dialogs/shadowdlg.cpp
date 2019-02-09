#include "shadowdlg.h"
#include "ui_shadowdlg.h"
#include "qmessagebox.h"
#include <QApplication>
#include <QDesktopWidget>
shadowdlg::shadowdlg(int x, int y,int width,int height, QWidget *parent):
    QDialog(parent),
    ui(new Ui::shadowdlg)
{
    ui->setupUi(this);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    parent_width = (int)(screenRect.width());
    parent_height = (int)(screenRect.height());
    this->setGeometry(0,0,parent_width,parent_height);
    initFrame(x,y,width,height);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

//    m_pTimer = new QTimer(this);
//    m_pTimer->setSingleShot(true);
    connect(ui->button,SIGNAL(clicked()), this, SLOT(closewindow()));
}

shadowdlg::~shadowdlg()
{
//    if(m_pTimer != Q_NULLPTR)
//        m_pTimer->deleteLater();

    delete ui;
}

void shadowdlg::startTimer()
{
//    m_pTimer->start(3000);
}

void shadowdlg::closewindow()
{
    this->close();
//    m_pTimer->start(3000);
}

void shadowdlg::initFrame(int x, int y,int width,int height)
{
//    ui->s1->setGeometry(0,0,x,y);
//    ui->s2->setGeometry(x+1,0,width,y);
//    ui->s3->setGeometry(x+width+1,0,parent_width-(x+width+1),y);
//    ui->s4->setGeometry(0,y+1,x,height);
//    ui->s5->setGeometry(x+width+1,y+1,parent_width-(x+width+1),height);
//    ui->s6->setGeometry(0,y+height+1,x,parent_height-(y+height+1));
//    ui->s7->setGeometry(x+1,y+height+1,width,parent_height-(y+height+1));
//    ui->s8->setGeometry(x+width+1,y+height+1,parent_width-(x+width+1),parent_height-(y+height+1));
//    ui->message->setGeometry(x+1,y+height+1,width,parent_height-(y+height+1));
//    ui->button->setGeometry(x+width+1,y+height+1,parent_width-(x+width+1),parent_height-(y+height+1));
    ui->s1->setGeometry(0,0,x,y);
    ui->s2->setGeometry(x,0,width,y);
    ui->s3->setGeometry(x+width,0,parent_width-(x+width),y);
    ui->s4->setGeometry(0,y,x,height);
    ui->s5->setGeometry(x+width,y,parent_width-(x+width),height);
    ui->s6->setGeometry(0,y+height,x,parent_height-(y+height));
    ui->s7->setGeometry(x,y+height,width,parent_height-(y+height));
    ui->s8->setGeometry(x+width,y+height,parent_width-(x+width),parent_height-(y+height));
    ui->message->setGeometry(x,y+height,200,25);
    ui->message->adjustSize();
    ui->button->setGeometry(x+ui->message->width(),y+height,30,30);
}

