// Class: ContentManagementInterface
// Type: UI/Control
// Description:
//   this class is provides a UI dialog for selecting the
//   ContentManagement operation that the user wishes to
//   perform. It also serves as the control class for the
//   small interface subsystem, since it will simply create
//   the operation-specific controller and pass the control
//   to it.

#ifndef CONTENTMANAGEMENTINTERFACE_H
#define CONTENTMANAGEMENTINTERFACE_H

#include "ClientNetworkHandler.h"
#include "ManageContentControl.h"

#include <QDialog>

namespace Ui {
class ContentManagementInterface;
}

class ContentManagementInterface : public QDialog
{
    Q_OBJECT

public:
    explicit ContentManagementInterface(QWidget *parent = 0,
                                        ClientNetworkHandler *net = NULL);
    ~ContentManagementInterface();

public slots:
    void navigateBack();

private slots:
    void on_manageContentButton_clicked();
    void on_manageCoursesButton_clicked();

private:
    Ui::ContentManagementInterface *ui;
    ClientNetworkHandler *network;
    ManageContentControl *contentManagementCtrl;
    // TODO: add management control/network classes here.

};

#endif // CONTENTMANAGEMENTINTERFACE_H
