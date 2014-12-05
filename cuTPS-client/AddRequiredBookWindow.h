#ifndef ADDREQUIREDBOOKWINDOW_H
#define ADDREQUIREDBOOKWINDOW_H

#include <QDialog>

namespace Ui {
class AddRequiredBookWindow;
}

class AddRequiredBookWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddRequiredBookWindow(QWidget *parent = 0);
    ~AddRequiredBookWindow();

private:
    Ui::AddRequiredBookWindow *ui;
};

#endif // ADDREQUIREDBOOKWINDOW_H
