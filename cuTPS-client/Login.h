// Class: Login
// Description:
//   Provides a GUI dialog for the user to enter
//   their credentials.
// Traceability:
//   LoginWindow in the LoginInterface subsystem

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

#include "ClientNetworkHandler.h"

// Forward declare LoginControl to avoid circular dependency
class LoginControl;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0,
                   ClientNetworkHandler *network = NULL,
                   LoginControl *loginC = NULL);
    void clearFields();
    ~Login();

private slots:
    void on_loginButton_clicked();

    void on_cancelButton_clicked();

    void on_connected();

private:
    Ui::Login *ui;
    ClientNetworkHandler *network;
    LoginControl *loginCtrl;

};

#endif // LOGIN_H
