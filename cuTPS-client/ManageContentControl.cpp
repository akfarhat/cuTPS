#include "ManageContentControl.h"
#include "ContentManagementInterface.h"

ManageContentControl::ManageContentControl(ContentManagementInterface *backWin,
                                           ClientNetworkHandler *networking)
{
    cmIF = backWin;

    requestAPI = new ContentRequestAPI(0, networking);

    contentManagementWin = new ManageContentListWindow(0, this, requestAPI); // will also pass networking
    contentManagementWin->show();

    // When a management window clicks back, we want the original menu interface.
    connect(contentManagementWin, SIGNAL(navigateBack()),
            cmIF, SLOT(navigateBack()));

    // TODO: connect slots for requests that the networking will signal
}

ManageContentControl::~ManageContentControl() {
    delete contentManagementWin;
    delete requestAPI;
}
