#include <QDialog>
#include <QTimer>

enum MsgType
{
    Msg_Praise = 0,
    Msg_Warning = 1,
    Msg_Error = 2,
    Msg_msg = 3
};

namespace Ui {
class MsgDlg;
}

class MsgDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MsgDlg(MsgType type, const QString &msg, QWidget *parent = 0);
    ~MsgDlg();
 
    void startTimer();
    
private:
    void initFrame(MsgType type,const QString &msg);
private:
    Ui::MsgDlg *ui;
    MsgType m_type;
    QTimer *m_pTimer;
};
