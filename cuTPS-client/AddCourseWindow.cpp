#include "AddCourseWindow.h"
#include "ui_AddCourseWindow.h"

AddCourseWindow::AddCourseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCourseWindow)
{
    ui->setupUi(this);
}

AddCourseWindow::~AddCourseWindow()
{
    delete ui;
}

void AddCourseWindow::on_cancelButton_clicked()
{
    this->close();
}

void AddCourseWindow::on_saveCourseButton_clicked()
{\
    QString code = this->ui->courseCodeEdit->text();
    QString name = this->ui->courseNameEdit->text();
    emit saveNewCourse(code, name);

    this->close();
}
