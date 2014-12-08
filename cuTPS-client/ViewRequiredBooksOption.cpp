#include "ViewRequiredBooksOption.h"
#include "ui_ViewRequiredBooksOption.h"

#include <QDebug>

ViewRequiredBooksOption::ViewRequiredBooksOption(QWidget *parent) : QWidget(parent), ui(new Ui::ViewRequiredBooksOption) {
    ui->setupUi(this);
}

ViewRequiredBooksOption::~ViewRequiredBooksOption() {
    delete ui;
}

void ViewRequiredBooksOption::on_viewBooksButton_clicked() {
    qDebug() << "View books button clicked...wooohooo!!";
}
