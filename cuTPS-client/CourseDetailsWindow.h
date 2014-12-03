// Traceability:
//   CourseDetailsWindow class
//   in the CourseManagement subsystem

#ifndef COURSEDETAILSWINDOW_H
#define COURSEDETAILSWINDOW_H

#include <QMainWindow>

#include "CourseRequestAPI.h"

// Forward reference to avoid circular deps
class ManageCourseControl;

namespace Ui {
class CourseDetailsWindow;
}

class CourseDetailsWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void courseNavigateBack();

public:
    explicit CourseDetailsWindow(QWidget *parent = 0,
                                 ManageCourseControl *ctrl = NULL,
                                 CourseRequestAPI *api = NULL);
    ~CourseDetailsWindow();

private slots:
    void on_backButton_clicked();

private:
    Ui::CourseDetailsWindow *ui;
    ManageCourseControl *manageCourseCtrl;
    CourseRequestAPI *requestAPI;

    void displayCourseList();
    void dispayCouseDetails(Course);
};

#endif // COURSEDETAILSWINDOW_H
