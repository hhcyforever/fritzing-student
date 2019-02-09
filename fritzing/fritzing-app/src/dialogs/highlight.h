#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <QDialog>

namespace Ui {
class highlight;
}

class highlight : public QDialog
{
    Q_OBJECT

public:
    explicit highlight(QWidget *parent = 0);
    ~highlight();

private:
    Ui::highlight *ui;
};

#endif // HIGHLIGHT_H
