#include "StudentMainMenuWindow.h"
#include "ui_StudentMainMenuWindow.h"

#include <QDebug>

StudentMainMenuWindow::StudentMainMenuWindow(QWidget *parent, ClientNetworkHandler *net) : QDialog(parent), ui(new Ui::StudentMainMenuWindow), network(net) {
    ui->setupUi(this);

    this->setWindowTitle("Carleton University Textbook Publishing System");

    // Create the buttons
    viewCartOption = new ViewCartOption(this, network);
    viewRequiredBooksOption = new ViewRequiredBooksOption(this, network);

    ui->verticalLayout->addWidget(viewCartOption);
    ui->verticalLayout->addWidget(viewRequiredBooksOption);
}

StudentMainMenuWindow::~StudentMainMenuWindow() {
    delete viewCartOption;
    delete viewRequiredBooksOption;
    delete ui;
}
