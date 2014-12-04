// Class: StudentMainMenuWindow
// Type: Boundary
// Description:
//     this class provides the main window for student users
//
// Traceability: StudentMainMenuWindow class in the StudentInterface subsystem

#ifndef STUDENTMAINMENUWINDOW_H
#define STUDENTMAINMENUWINDOW_H

#include <QDialog>
#include "ViewCartOption.h"
#include "ViewRequiredBooksOption.h"
#include "ClientNetworkHandler.h"
#include "Entity/Student.h"


namespace Ui {
    class StudentMainMenuWindow;
}

class StudentMainMenuWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentMainMenuWindow(QWidget *parent = 0, ClientNetworkHandler *net = NULL, Student *stu = NULL);
    ~StudentMainMenuWindow();

    Student *getStudent();
    void setStudent(Student *);

private:
    Ui::StudentMainMenuWindow *ui;
    ViewCartOption *viewCartOption;
    ViewRequiredBooksOption *viewRequiredBooksOption;

    ClientNetworkHandler *network;

    Student *student;

};

#endif // STUDENTMAINMENUWINDOW_H
