#include "ManageContentControl.h"
#include "ContentManagementInterface.h"

ManageContentControl::ManageContentControl(ContentManagementInterface *backWin)
{
    cmIF = backWin;

    contentManagementWin = new ManageContentListWindow(0, this); // will also pass networking
    contentManagementWin->show();

    // When a management window clicks back, we want the original menu interface.
    connect(contentManagementWin, SIGNAL(navigateBack()),
            cmIF, SLOT(navigateBack()));

    // TODO: connect slots for requests that the networking will signal
}
