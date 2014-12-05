#include "AddRequiredBookWindow.h"
#include "ui_AddRequiredBookWindow.h"

AddRequiredBookWindow::AddRequiredBookWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRequiredBookWindow)
{
    ui->setupUi(this);
}

AddRequiredBookWindow::~AddRequiredBookWindow()
{
    delete ui;
}
