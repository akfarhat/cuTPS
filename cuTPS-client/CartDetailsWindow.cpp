#include "CartDetailsWindow.h"
#include "ui_CartDetailsWindow.h"

#include <QDebug>

CartDetailsWindow::CartDetailsWindow(QWidget *parent, ViewCartControl *ctrl, CartRequestsAPI *api)  : QMainWindow(parent),  ui(new Ui::CartDetailsWindow), viewCartCtrl(ctrl), requestAPI(api) {

    ui->setupUi(this);

    ui->itemList->setEnabled(false);
    ui->typeList->setEnabled(false);
    ui->priceList->setEnabled(false);
    ui->totalPrice->setEnabled(false);

    // Populate the lists
    for (SellableItem *item: viewCartCtrl->getStudent()->getCart()->getItems()) {
        ui->itemList->addItem(item->getName());
        ui->typeList->addItem(item->getType());
        ui->priceList->addItem("$" + QString::number(item->getPriceCents() / 100.00f));
    }

    ui->totalPrice->setText(QString::number(viewCartCtrl->getStudent()->getCart()->getTotalPrice() / 100.00f));
}

CartDetailsWindow::~CartDetailsWindow() {
    delete ui;
}

void CartDetailsWindow::on_backButton_clicked() {
    this->close();
}

void CartDetailsWindow::on_cancelOrderButton_clicked() {
    qDebug() << "Cancel order button clicked";

    CancelOrderControl *cancelOrderCtrl = new CancelOrderControl();

    cancelOrderCtrl->clearCart(viewCartCtrl->getStudent());
    delete cancelOrderCtrl;

    ui->itemList->clear();
    ui->typeList->clear();
    ui->priceList->clear();
    ui->totalPrice->setText("0");

    this->hide();
}

void CartDetailsWindow::on_placeOrderButton_clicked() {
    qDebug() << "Place order button clicked";
}
