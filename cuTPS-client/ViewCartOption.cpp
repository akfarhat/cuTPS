#include "ViewCartOption.h"
#include "ui_ViewCartOption.h"

#include <QDebug>

ViewCartOption::ViewCartOption(QWidget *parent) : QWidget(parent), ui(new Ui::ViewCartOption) {
    ui->setupUi(this);
}

ViewCartOption::~ViewCartOption() {
    delete ui;
}


void ViewCartOption::on_viewCartButton_clicked() {
    qDebug() << "view cart button clicked...woohoo!!";
}
