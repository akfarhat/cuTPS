#include "CartDetailsWindow.h"
#include "ui_CartDetailsWindow.h"

#include <QDebug>

CartDetailsWindow::CartDetailsWindow(QWidget *parent, ViewCartControl *ctrl, CartRequestsAPI *api)  : QMainWindow(parent),  ui(new Ui::CartDetailsWindow), viewCartCtrl(ctrl), requestAPI(api) {

    ui->setupUi(this);

    ui->itemList->setEnabled(false);
    ui->typeList->setEnabled(false);
    ui->priceList->setEnabled(false);
    ui->totalPrice->setEnabled(false);

}

CartDetailsWindow::~CartDetailsWindow() {
    delete ui;
}

void CartDetailsWindow::on_backButton_clicked() {
    this->close();
}

void CartDetailsWindow::on_cancelOrderButton_clicked() {
    qDebug() << "Cancel order button clicked";
}

void CartDetailsWindow::on_placeOrderButton_clicked() {
    qDebug() << "Place order button clicked";
}
