// Class: LoginWindow
// Type: User Interface
// Description:
//     This class provides the UI window for the
//     login option

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;

private slots:
    // Event handlers for button clicks
    void cancelButtonClickHandler();
    void loginButtonClickHandler();
};

#endif // LOGINWINDOW_H
