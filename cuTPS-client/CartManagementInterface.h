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
#include "ViewRequiredBooksControl.h"
#include "ViewCartControl.h"
#include "CartRequestsAPI.h"

namespace Ui {
    class CartManagementInterface;
}

class CartManagementInterface : public QDialog
{
    Q_OBJECT

public:
    explicit CartManagementInterface(QWidget *, ClientNetworkHandler *, Student *);
    ~CartManagementInterface();

    Student* getStudent();


private slots:
    void on_viewCartButton_clicked();
    void on_viewBooksButton_clicked();

    void viewBooksControlFinished();
    void viewCartControlFinished();


private:
    Ui::CartManagementInterface *ui;

    ClientNetworkHandler *network;
    CartRequestsAPI *requestAPI;

    Student *student;

    ViewCartControl *viewCartCtrl;
    ViewRequiredBooksControl *viewBooksCtrl;

};

#endif // CARTMANAGEMENTINTERFACE_H
