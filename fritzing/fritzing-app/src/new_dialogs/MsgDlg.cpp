#include "Msgdlg.h"
#include "ui_Msgdlg.h"
#include "qmessagebox.h"
MsgDlg::MsgDlg(MsgType type, const QString &msg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgDlg),
    m_type(type)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
 
    initFrame(type,msg);
 
    m_pTimer = new QTimer(this);
    m_pTimer->setSingleShot(true);
    connect(m_pTimer, &QTimer::timeout, this, [=](){this->close();});
}
 
MsgDlg::~MsgDlg()
{
    if(m_pTimer != Q_NULLPTR)
        m_pTimer->deleteLater();
 
    delete ui;
}
 
void MsgDlg::startTimer()
{
    m_pTimer->start(3000);
}
 
void MsgDlg::initFrame(MsgType type,const QString &msg)
{
    if(type == Msg_msg){
        QString newMsg = "\n    "+msg+"    \n";
        ui->MsgLabelText->setStyleSheet("QLabel{border-image: url(../fritzing-app/resources/images/dialog_background.jpg);}");
        ui->MsgLabelText->setText(newMsg);
        ui->MsgLabelText->setWordWrap(true);
        ui->MsgLabelText->adjustSize();
    }
    else if(type == Msg_Praise){
        QString filename("../fritzing-app/resources/images/good2.jpg");
        QImage* img=new QImage;
        if(! ( img->load(filename) ) )
        {
            QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
            delete img;
            return;
        }
        ui->MsgLabel->setPixmap(QPixmap::fromImage(*img));
    }

}

