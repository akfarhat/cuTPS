// Class: ViewRequiredBooksControl
// Type: Control
// Description:
//     This class is responsible for invoking the client
//     side API method in the Cart Request API for requesting
//     the list of available books for the current user

#ifndef VIEWREQUIREDBOOKSCONTROL_H
#define VIEWREQUIREDBOOKSCONTROL_H

#include <QUuid>
#include <QVector>
#include <QObject>
#include "ClientNetworkHandler.h"
#include "CartRequestsAPI.h"
#include "AvailableItemWindow.h"

class ViewRequiredBooksControl: public QObject {
    Q_OBJECT

public:
    ViewRequiredBooksControl(CartRequestsAPI *);
    ~ViewRequiredBooksControl();

    // Get the list of required books for this user
    QUuid getRequiredBooks();
    void launchAvailableItemWindow();

signals:
    void viewBooksControlFinished();

private slots:
    void requiredBooksReceived(QUuid requestId, int code, QMap<Course*, QList<Textbook*>*>*);
    void availableItemWindowClosed();

private:

    CartRequestsAPI *requestAPI;
    AvailableItemWindow *itemWindow;

};

#endif // VIEWREQUIREDBOOKSCONTROL_H
