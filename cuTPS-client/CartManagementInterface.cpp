#include "CartManagementInterface.h"
#include "ui_CartManagementInterface.h"

CartManagementInterface::CartManagementInterface(QWidget *parent, ClientNetworkHandler *netHandler) :
    QDialog(parent),
    ui(new Ui::CartManagementInterface),
    network(netHandler)
{
    student = new Student();
    requestAPI = new CartRequestsAPI(0, network, student);

    ui->setupUi(this);

    this->setWindowTitle("Carleton University Textbook Publishing System");

}

CartManagementInterface::~CartManagementInterface()
{
    delete student;
    delete requestAPI;
    delete viewCartCtrl;
    delete viewBooksCtrl;
    delete ui;
}

Student* CartManagementInterface::getStudent()
{
    return student;
}

void CartManagementInterface::on_viewCartButton_clicked()
{
    qDebug() << "view cart button clicked...showing cart details window";


    viewCartCtrl = new ViewCartControl(requestAPI);

    // Make sure this class knows when ViewCartControl is done so it can free the viewCartCtrl pointer
    QObject::connect(viewCartCtrl, SIGNAL(viewCartControlFinished()), this, SLOT(viewCartControlFinished()));

    viewCartCtrl->launchCartDetailsWindow();

}

void CartManagementInterface::on_viewBooksButton_clicked()
{
    qDebug() << "View books button clicked...showing the available item window";

    viewBooksCtrl = new ViewRequiredBooksControl(requestAPI);

    // Make sure this class knows when ViewRequiredBooksControl is done so it can free the viewBooksCtrl pointer
    QObject::connect(viewBooksCtrl, SIGNAL(viewBooksControlFinished()), this, SLOT(viewBooksControlFinished()));

    viewBooksCtrl->launchAvailableItemWindow();
}


void CartManagementInterface::viewCartControlFinished()
{
    delete viewCartCtrl;
    qDebug() << "CartManagementInterface::viewCartControlFinished: deleted viewCartCtrl";
    viewCartCtrl = NULL;
}


void CartManagementInterface::viewBooksControlFinished()
{
    delete viewBooksCtrl;
    qDebug() << "CartManagementInterface::ViewBooksControlFinished: deleted viewBooksCtrl";
    viewBooksCtrl = NULL;
}

