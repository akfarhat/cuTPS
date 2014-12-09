#include "BillingWindow.h"
#include "ui_BillingWindow.h"

#include <QDebug>

BillingWindow::BillingWindow(QWidget *parent, PlaceOrderControl *control) :
    QDialog(parent),
    ui(new Ui::BillingWindow),
    placeOrderCtrl(control)
{
    ui->setupUi(this);

    this->setWindowTitle("Order Information");

    ui->errorLabel->hide();

    // Fill in the fields with any saved information for the student
    if (placeOrderCtrl->getStudent() != NULL) {
        if (placeOrderCtrl->getStudent()->getCreditCardInfo()) {
            ui->nameField->setText(placeOrderCtrl->getStudent()->getCreditCardInfo()->getName());
            ui->numberField->setText(placeOrderCtrl->getStudent()->getCreditCardInfo()->getCardNumber());
            ui->expiryField->setText(placeOrderCtrl->getStudent()->getCreditCardInfo()->getExpiry());
            ui->codeField->setText(placeOrderCtrl->getStudent()->getCreditCardInfo()->getSecurityCode());
        }
        if (placeOrderCtrl->getStudent()->getDeliveryInfo()) {
            ui->emailField->setText(placeOrderCtrl->getStudent()->getDeliveryInfo()->getEmailAddress());
        }
    }
}

BillingWindow::~BillingWindow()
{
    delete ui;
}

void BillingWindow::on_cancelButton_clicked()
{
    qDebug() << "Cancel button was clicked in billing window";

    placeOrderCtrl = NULL;
    this->close();
}

void BillingWindow::on_submitButton_clicked()
{
    qDebug() << "Submit button was clicked in billing window";

    placeOrderCtrl->submitOrder();

    placeOrderCtrl = NULL;
    this->close();
}
