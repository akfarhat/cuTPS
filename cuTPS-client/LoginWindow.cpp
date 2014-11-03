#include "LoginWindow.h"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow) {

    ui->setupUi(this);
    this->setWindowTitle("CUTPS - Login");

    ui->passwordInput->setEchoMode(QLineEdit::Password);

    // Connect the cancel button to its handler
    this->connect(this->ui->cancelButton,
                  SIGNAL(clicked()),
                  this,
                  SLOT(cancelButtonClickHandler()));
    // Connect the login button to its handler
    this->connect(this->ui->loginButton,
                  SIGNAL(clicked()),
                  this,
                  SLOT(loginButtonClickHandler()));

}

LoginWindow::~LoginWindow() {
    delete ui;
}

// Called when the cancel button is clicked
void LoginWindow::cancelButtonClickHandler() {
    this->close();
}

// Called when the login button is clicked
void LoginWindow::loginButtonClickHandler() {
    // Appends password and username to username field.. just for testing
    //this->ui->usernameInput->setText(
    //            this->ui->passwordInput->text() +
    //            this->ui->usernameInput->text());
}
