#ifndef STUDENTMAINMENUWINDOW_H
#define STUDENTMAINMENUWINDOW_H

#include <QDialog>
#include "ViewCartOption.h"
#include "ViewRequiredBooksOption.h"

namespace Ui {
    class StudentMainMenuWindow;
}

class StudentMainMenuWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentMainMenuWindow(QWidget *parent = 0);
    ~StudentMainMenuWindow();

public slots:


private slots:


private:
    Ui::StudentMainMenuWindow *ui;
    ViewCartOption *viewCartOption;
    ViewRequiredBooksOption *viewRequiredBooksOption;


};

#endif // STUDENTMAINMENUWINDOW_H
