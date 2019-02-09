#ifndef DIALOG_ADDITEM_H
#define DIALOG_ADDITEM_H

#include <QDialog>

namespace Ui {
class dialog_additem;
}

class dialog_additem : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_additem(QWidget *parent = 0);
    ~dialog_additem();

private slots:
    void on_okButton_clicked();

    void on_introductonButton_clicked();

private:
    Ui::dialog_additem *ui;
};

#endif // DIALOG_ADDITEM_H
