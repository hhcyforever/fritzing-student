#include <QDialog>
#include <QTimer>

namespace Ui {
class shadowdlg;
}

class shadowdlg : public QDialog
{
    Q_OBJECT

public:
    explicit shadowdlg(int x, int y,int width,int height, QWidget *parent = 0);
    ~shadowdlg();

    void startTimer();

private:
    void initFrame(int x, int y,int width,int height);
private:
    int parent_width;
    int parent_height;
    Ui::shadowdlg *ui;
    QTimer *m_pTimer;
protected slots:
    void closewindow();
};
