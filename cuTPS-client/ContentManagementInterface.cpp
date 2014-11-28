#include "ContentManagementInterface.h"
#include "ui_ContentManagementInterface.h"

#include <QDebug>

ContentManagementInterface::ContentManagementInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContentManagementInterface)
{
    ui->setupUi(this);
}

ContentManagementInterface::~ContentManagementInterface()
{
    delete ui;
}

void ContentManagementInterface::on_addCourseButton_clicked()
{
    qDebug() << "ContentManagementInterface::addCourseButton";
}

void ContentManagementInterface::on_modifyCourseButton_clicked()
{
    qDebug() << "ContentManagementInterface::modifyCourseButton";
}

void ContentManagementInterface::on_manageContentButton_clicked()
{
    qDebug() << "ContentManagementInterface::ManageContent";
}
