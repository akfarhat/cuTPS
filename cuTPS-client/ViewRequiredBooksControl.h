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
#include "Entity/Student.h"
#include "ClientNetworkHandler.h"
#include "CartRequestsAPI.h"
#include "AvailableItemWindow.h"

class ViewRequiredBooksControl: public QObject {
    Q_OBJECT;


    public:
        ViewRequiredBooksControl(CartRequestsAPI *);
        ~ViewRequiredBooksControl();

        // Get the list of required books for this user
        QUuid getRequiredBooks(QString&);

        // Request the details of a particular textbook id
        QUuid getBookDetails(const qint32 id);

        // Request details for a list of textbook ids
        QUuid getBookDetails(const QVector<qint32>& ids);

        void launchAvailableItemWindow();


    signals:
        void viewBooksControlFinished();

    private slots:
        void textbookLookupCompleted(QUuid requestId, int code, QVector<qint32>* booksIds);
        void textbookDetailsReceived(QUuid requestId, int code, QVector<Textbook*>* books);

        void availableItemWindowClosed();
    private:
        CartRequestsAPI *requestAPI;

        AvailableItemWindow *itemWindow;

};

#endif // VIEWREQUIREDBOOKSCONTROL_H
