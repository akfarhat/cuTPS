#include "CartDetailsWindow.h"
#include "ui_CartDetailsWindow.h"

#include <QDebug>

CartDetailsWindow::CartDetailsWindow(QWidget *parent, CartRequestsAPI *api)  : QDialog(parent),  ui(new Ui::CartDetailsWindow), requestAPI(api) {

    ui->setupUi(this);

    this->setWindowTitle("Shopping Cart Details");

    ui->itemList->setEnabled(false);
    ui->typeList->setEnabled(false);
    ui->priceList->setEnabled(false);
    ui->totalPrice->setEnabled(false);

    ui->message->hide();

    updateView();

}

CartDetailsWindow::~CartDetailsWindow() {
    requestAPI = NULL;
    if (placeOrderCtrl != NULL)
        delete placeOrderCtrl;
    delete ui;
}

void CartDetailsWindow::setError(QString message) {
    ui->message->setStyleSheet("QLabel { color : red; }");
    ui->message->setText(message);
    ui->message->show();
}

void CartDetailsWindow::setMessage(QString message) {
    ui->message->setStyleSheet("QLabel { color : green; }");
    ui->message->setText(message);
    ui->message->show();
}

void CartDetailsWindow::updateView() {
    ui->message->hide();

    // Clear the lists
    ui->itemList->clear();
    ui->typeList->clear();
    ui->priceList->clear();

    // Populate the lists
    for (SellableItem *item: requestAPI->getStudent()->getCart()->getItems()) {
        ui->itemList->addItem(item->getName());
        ui->typeList->addItem(item->getType());
        ui->priceList->addItem("$" + QString::number(item->getPriceCents() / 100.00f));
    }

    ui->totalPrice->setText(QString::number(requestAPI->getStudent()->getCart()->getTotalPrice() / 100.00f));

    // Disable place order and cancel order buttons if cart is empty
    if (requestAPI->getStudent()->getCart()->getItems().empty()) {
        ui->cancelOrderButton->setEnabled(false);
        ui->placeOrderButton->setEnabled(false);
    }
}


void CartDetailsWindow::on_backButton_clicked() {
    requestAPI = NULL;
    this->close();
    emit cartDetailsWindowClosed();
}

void CartDetailsWindow::on_cancelOrderButton_clicked() {
    qDebug() << "Cancel order button clicked";

    CancelOrderControl *cancelOrderCtrl = new CancelOrderControl();

    cancelOrderCtrl->clearCart(requestAPI->getStudent());
    delete cancelOrderCtrl;


    requestAPI = NULL;
    this->close();
    emit cartDetailsWindowClosed();
}

void CartDetailsWindow::on_placeOrderButton_clicked() {
    qDebug() << "Place order button clicked";


    placeOrderCtrl = new PlaceOrderControl(this, requestAPI);

    QObject::connect(placeOrderCtrl, SIGNAL(placeOrderControlFinished()), this, SLOT(placeOrderControlFinished()));

    placeOrderCtrl->launchBillingWindow();

}

void CartDetailsWindow::placeOrderControlFinished()
{
    delete placeOrderCtrl;
    placeOrderCtrl = NULL;
    qDebug() << "CartDetailsWindow::placeOrderControlFinished: deleted placeOrderCtrl";
}
