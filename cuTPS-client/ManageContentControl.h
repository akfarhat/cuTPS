// Class: ManageContentControl
// Type: Control
// Description:
//   Handles the main window for the ContentManagement
// Traceability:
//   ManageContentControl class in the
//   ContentManagement subsystem.

#ifndef MANAGECONTENTCONTROL_H
#define MANAGECONTENTCONTROL_H

#include <QObject>

#include "ManageContentListWindow.h"
#include "ContentRequestAPI.h"
#include "ClientNetworkHandler.h"

// Forward decleration to avoid circular dep
class ContentManagementInterface;

class ManageContentControl : public QObject
{
    private:
        Q_OBJECT

    public:
        ManageContentControl(ContentManagementInterface *, ClientNetworkHandler *);
        ~ManageContentControl();

        ContentManagementInterface *cmIF;
        ManageContentListWindow *contentManagementWin;
        ContentRequestAPI *requestAPI; // Subsystem specific requests API
};

#endif // MANAGECONTENTCONTROL_H
