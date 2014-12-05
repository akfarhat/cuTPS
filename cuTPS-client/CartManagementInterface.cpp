#include "CartManagementInterface.h"
#include "ui_CartManagementInterface.h"

CartManagementInterface::CartManagementInterface(QWidget *parent, ClientNetworkHandler *net, Student *stu) :
    QDialog(parent),
    ui(new Ui::CartManagementInterface),
    network(net),
    student(stu)
{
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

    this->hide();

    ViewCartControl *viewCartCtrl = new ViewCartControl(this, network, student);



    viewCartCtrl->launchCartDetailsWindow();

}

void CartManagementInterface::on_viewBooksButton_clicked()
{
    qDebug() << "View books button clicked...wooohooo!!";
}
