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

    ui->message->hide();

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

void BillingWindow::setError(QString message) {
    ui->message->setStyleSheet("QLabel { color : red; }");
    ui->message->setText(message);
    ui->message->show();
}

bool BillingWindow::validateData()
{
    if (ui->nameField->text().isEmpty() ||
            ui->numberField->text().isEmpty() ||
            ui->expiryField->text().isEmpty() ||
            ui->codeField->text().isEmpty() ||
            ui->emailField->text().isEmpty())
    {
        setError("Error: all fields need to be filled in");
        return false;
    }
    return true;
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

    if (validateData()) {
        CreditCardInfo *cInfo = new CreditCardInfo(ui->nameField->text(), ui->emailField->text(), "", "", ui->nameField->text(), ui->numberField->text(), ui->expiryField->text(), ui->codeField->text());
        DeliveryInfo *dInfo = new DeliveryInfo(ui->emailField->text());
        placeOrderCtrl->getStudent()->setCreditCardInfo(cInfo);
        placeOrderCtrl->getStudent()->setDeliveryInfo(dInfo);

        placeOrderCtrl->submitOrder();

        delete cInfo;
        delete dInfo;

        placeOrderCtrl = NULL;
        this->close();
    }

}
