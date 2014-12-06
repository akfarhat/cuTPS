#include "CartManagementInterface.h"
#include "ui_CartManagementInterface.h"

CartManagementInterface::CartManagementInterface(QWidget *parent, ClientNetworkHandler *netHandler, Student *newStudent) :
    QDialog(parent),
    ui(new Ui::CartManagementInterface),
    network(netHandler),
    student(newStudent)
{
    requestAPI = new CartRequestsAPI(0, network, student);

    ui->setupUi(this);

    this->setWindowTitle("Carleton University Textbook Publishing System");

    // Create a new empty shopping cart
    if (student->getCart() == NULL) {
        student->setCart(new ShoppingCart());
    }

}

CartManagementInterface::~CartManagementInterface()
{
    delete ui;
}

Student* CartManagementInterface::getStudent()
{
    return student;
}

void CartManagementInterface::on_viewCartButton_clicked()
{
    qDebug() << "view cart button clicked...showing cart details window";

    // Hide this window
    this->hide();

    ViewCartControl *viewCartCtrl = new ViewCartControl(this, requestAPI);

    viewCartCtrl->launchCartDetailsWindow();

}

void CartManagementInterface::on_viewBooksButton_clicked()
{
    qDebug() << "View books button clicked...wooohooo!!";
}