#include "ContentManagementInterface.h"
#include "ui_ContentManagementInterface.h"

#include <QDebug>

ContentManagementInterface::ContentManagementInterface(QWidget *parent,
                                                       ClientNetworkHandler *net) :
    QDialog(parent),
    network(net),
    ui(new Ui::ContentManagementInterface)
{
    qDebug() << "ContentManagementInterface::CTOR";
    ui->setupUi(this);
}

ContentManagementInterface::~ContentManagementInterface()
{
    delete ui;
}

void ContentManagementInterface::on_manageContentButton_clicked()
{
    qDebug() << "ContentManagementInterface::ManageContent";

    // Create the control class for the management subsystem
    contentManagementCtrl = new ManageContentControl(this, network);

    // Hide this more general window for now
    this->hide();
}

void ContentManagementInterface::on_manageCoursesButton_clicked()
{
    qDebug() << "ContentManagementInterface::ManageCourses";
}

void ContentManagementInterface::navigateBack() {
    // Handles signals from lower back button on
    // management windows.

    delete contentManagementCtrl;

    this->show();
}
