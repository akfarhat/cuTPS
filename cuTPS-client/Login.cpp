#include "Login.h"
#include "ui_Login.h"
#include "Utils.h"
#include "LoginControl.h"
#include "ContentManagementInterface.h"
#include "ui_ContentManagementInferface.h"

#include <QDebug>

Login::Login(QWidget *parent, ClientNetworkHandler *net) :
    QDialog(parent),
    ui(new Ui::Login),
    network(net)
{
    ui->setupUi(this);

    connect(network, SIGNAL(loginSuccessful(QUuid)), this, SLOT(loginSuccessful(QUuid)));
    connect(network, SIGNAL(loginFailed(QUuid)), this, SLOT(loginFailed(QUuid)));
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    UserCredentials userCreds;
    userCreds.username = ui->usernameField->text();
    userCreds.password = ui->passwordField->text();

    qDebug() << "Logging in.. username: '" << userCreds.username
             << "', password: '" << userCreds.password << "'";

    SessionCredentials sessCreds;
    sessCreds.sessionID = 0;

    LoginControl *loginCtrl = new LoginControl(network);

    QUuid requestId;

    loginCtrl->login(requestId, userCreds);

    // TODO: if login was successful, create a Menu for the
    // correct user type, give the MenuWindow a new instance
    // of the subset network handler that references this one's.

    delete loginCtrl;
}

void Login::on_cancelButton_clicked()
{
    qDebug() << "Cancel button selected. Goodbye cruel world.";

    this->close();
}

void Login::loginSuccessful(QUuid requestId) {
    qDebug() << "Login::successfulLogin for: " << requestId;

    ContentManagementInterface cmInterface;
    cmInterface.show();

    qDebug() << "Login::finished creating cmInterface";

    //ui->setupUi(&cmInterface);

    qDebug() << "Login::finished setting up new UI";

    ui->usernameField->clear();
    ui->passwordField->clear();

    qDebug() << "Login::cleared fields";
}

void Login::loginFailed(QUuid requestId) {
    qDebug() << "Login::failedLogin for: " << requestId;
}
