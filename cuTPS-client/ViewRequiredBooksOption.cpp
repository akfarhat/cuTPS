#include "ViewRequiredBooksOption.h"
#include "ui_ViewRequiredBooksOption.h"

#include <QDebug>

ViewRequiredBooksOption::ViewRequiredBooksOption(QWidget *parent, ClientNetworkHandler *net) : QWidget(parent), ui(new Ui::ViewRequiredBooksOption), network(net) {
    ui->setupUi(this);
}

ViewRequiredBooksOption::~ViewRequiredBooksOption() {
    delete ui;
}

void ViewRequiredBooksOption::on_viewBooksButton_clicked() {
    qDebug() << "View books button clicked...wooohooo!!";
}
