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

    this->contentManagementCtrl = NULL;
    this->courseManagementCtrl = NULL;

    ui->setupUi(this);
}

ContentManagementInterface::~ContentManagementInterface()
{
    delete ui;

    if (this->contentManagementCtrl != NULL)
        delete this->contentManagementCtrl;

    if (this->courseManagementCtrl != NULL)
        delete this->courseManagementCtrl;
}

void ContentManagementInterface::on_manageContentButton_clicked()
{
    qDebug() << "ContentManagementInterface::ManageContent";

    // Create the control class for the content management subsystem
    contentManagementCtrl = new ManageContentControl(this, network);

    this->hide();
}

void ContentManagementInterface::on_manageCoursesButton_clicked()
{
    qDebug() << "ContentManagementInterface::ManageCourses";

    // Create the control class for the course management subsystem
    courseManagementCtrl = new ManageCourseControl(this, network);

    this->hide();
}

void ContentManagementInterface::navigateBack()
{
    // Handles signals from lower back button on
    // management windows.

    if (this->contentManagementCtrl != NULL) {
        delete this->contentManagementCtrl;
        this->contentManagementCtrl = NULL;
    }

    this->show();
}

void ContentManagementInterface::courseNavigateBack()
{
    if (this->courseManagementCtrl != NULL) {
        delete this->courseManagementCtrl;
        this->courseManagementCtrl = NULL;
    }

    this->show();
}
