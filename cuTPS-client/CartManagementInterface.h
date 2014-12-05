// Class: CartManagementInterface
// Type: Boundary
// Description:
//   this class provides the UI for student users.
//   It contains options for student users to view/manage
//   their shopping cart, and view available textbooks which
//   they can purchase.
// Traceability:
//   Subsystem: StudentInterface
//   Classes: StudentMainMenuWindow, ViewCartOption, ViewRequiredBooksOption
//

#ifndef CARTMANAGEMENTINTERFACE_H
#define CARTMANAGEMENTINTERFACE_H

#include <QDialog>
#include "ClientNetworkHandler.h"
#include "Entity/Student.h"
#include "ViewBookDetailsControl.h"
#include "ViewCartControl.h"

namespace Ui {
    class CartManagementInterface;
}

class CartManagementInterface : public QDialog
{
    Q_OBJECT

public:
    explicit CartManagementInterface(QWidget *parent = 0, ClientNetworkHandler *net = NULL, Student *stu = NULL);
    ~CartManagementInterface();

    Student* getStudent();


private slots:
    void on_viewCartButton_clicked();
    void on_viewBooksButton_clicked();


private:
    Ui::CartManagementInterface *ui;

    ClientNetworkHandler *network;

    Student *student;
};

#endif // CARTMANAGEMENTINTERFACE_H
