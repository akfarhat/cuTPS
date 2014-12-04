#include "ViewCartOption.h"
#include "ui_ViewCartOption.h"

#include <QDebug>

ViewCartOption::ViewCartOption(QWidget *parent, ClientNetworkHandler *net) : QWidget(parent), ui(new Ui::ViewCartOption), network(net) {
    ui->setupUi(this);
}

ViewCartOption::~ViewCartOption() {
    delete ui;
}


void ViewCartOption::on_viewCartButton_clicked() {
    qDebug() << "view cart button clicked...showing cart details window";

    ViewCartControl *viewCartCtrl = new ViewCartControl(network);



    viewCartCtrl->launchCartDetailsWindow();

}
