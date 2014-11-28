#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

#include "ClientNetworkHandler.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0, ClientNetworkHandler *network = NULL);
    ~Login();

private slots:
    void on_loginButton_clicked();

    void on_cancelButton_clicked();

    void loginSuccessful(QUuid);

    void loginFailed(QUuid);

private:
    Ui::Login *ui;
    ClientNetworkHandler *network;

};

#endif // LOGIN_H
