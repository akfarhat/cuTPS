#ifndef MANAGECONTENTCONTROL_H
#define MANAGECONTENTCONTROL_H

#include <QObject>

#include "ManageContentListWindow.h"

// Forward decleration to avoid circular dep
class ContentManagementInterface;

class ManageContentControl : public QObject
{
    private:
        Q_OBJECT

    public:
        ManageContentControl(ContentManagementInterface *);
        ContentManagementInterface *cmIF;
        ManageContentListWindow *contentManagementWin;
};

#endif // MANAGECONTENTCONTROL_H
