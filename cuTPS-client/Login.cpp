#include "Login.h"
#include "ui_Login.h"
#include "Defines.h"
#include "LoginControl.h"

#include <QDebug>

Login::Login(QWidget *parent, ClientNetworkHandler *net, LoginControl *loginC) :
    QDialog(parent),
    ui(new Ui::Login),
    network(net)
{
    ui->setupUi(this);

    loginCtrl = loginC;
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    // Connect the network handler to the server
    QHostAddress address(TPSNetProtocolDef::remoteServerIp);
    network->connectToServer(address, 12754);

    connect(network, SIGNAL(connectedToServer()), this, SLOT(on_connected()));
}

void Login::on_cancelButton_clicked()
{
    qDebug() << "Cancel button selected. Goodbye cruel world.";

    this->close();
}

void Login::on_connected()
{
    UserCredentials userCreds;
    userCreds.username = ui->usernameField->text();
    userCreds.password = ui->passwordField->text();

    qDebug() << "Logging in.. username: '" << userCreds.username
             << "', password: '" << userCreds.password << "'";

    SessionCredentials sessCreds;
    sessCreds.sessionID = 0;

    QUuid requestId;

    loginCtrl->login(requestId, userCreds);
}

void Login::clearFields() {
    ui->usernameField->clear();
    ui->passwordField->clear();
}
