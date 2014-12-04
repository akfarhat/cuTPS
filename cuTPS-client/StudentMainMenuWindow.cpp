#include "StudentMainMenuWindow.h"
#include "ui_StudentMainMenuWindow.h"

#include <QDebug>

StudentMainMenuWindow::StudentMainMenuWindow(QWidget *parent, ClientNetworkHandler *net, Student *stu) : QDialog(parent), ui(new Ui::StudentMainMenuWindow), network(net), student(stu) {
    ui->setupUi(this);

    this->setWindowTitle("Carleton University Textbook Publishing System");

    // Create a new empty shopping cart
    if (student->getCart() == NULL) {
        student->setCart(new ShoppingCart());
    }

    // Create the buttons
    viewCartOption = new ViewCartOption(this, network);
    viewCartOption->setStudent(student);
    viewRequiredBooksOption = new ViewRequiredBooksOption(this, network, student);

    ui->verticalLayout->addWidget(viewCartOption);
    ui->verticalLayout->addWidget(viewRequiredBooksOption);
}

StudentMainMenuWindow::~StudentMainMenuWindow() {
    delete viewCartOption;
    delete viewRequiredBooksOption;
    delete ui;
}

Student* StudentMainMenuWindow::getStudent() {
    return student;
}

void StudentMainMenuWindow::setStudent(Student *newStudent) {
    student = newStudent;
}
