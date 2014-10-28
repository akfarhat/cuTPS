#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "Student.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow) {

    ui->setupUi(this);
    this->setWindowTitle("Login");

    ui->passwordInput->setEchoMode(QLineEdit::Password);

    // Connect the cancel button to its handler
    this->connect(this->ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClickHandler()));

}

LoginWindow::~LoginWindow() {
    delete ui;
}


void LoginWindow::cancelButtonClickHandler() {
    this->close();
}
