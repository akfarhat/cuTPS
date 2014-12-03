#include "CourseDetailsWindow.h"
#include "ui_CourseDetailsWindow.h"

CourseDetailsWindow::CourseDetailsWindow(QWidget *parent,
                                         ManageCourseControl *ctrl,
                                         CourseRequestAPI *api) :
    manageCourseCtrl(ctrl),
    requestAPI(api),
    QMainWindow(parent),
    ui(new Ui::CourseDetailsWindow)
{
    ui->setupUi(this);
}

CourseDetailsWindow::~CourseDetailsWindow()
{
    delete ui;
}

void CourseDetailsWindow::on_backButton_clicked()
{
    this->close();
    emit courseNavigateBack();
}
