#include "ViewRequiredBooksControl.h"

ViewRequiredBooksControl::ViewRequiredBooksControl(CartRequestsAPI *api)
    : requestAPI(api)
{
    itemWindow = NULL;

    connect(requestAPI->getNetwork(),
            SIGNAL(requiredBooksReceived(QUuid,int,QMap<Course*,QList<Textbook*>*>*)),
            this,
            SLOT(requiredBooksReceived(QUuid,int,QMap<Course*,QList<Textbook*>*>*)));
}

ViewRequiredBooksControl::~ViewRequiredBooksControl()
{
    requestAPI = NULL;
}

QUuid ViewRequiredBooksControl::getRequiredBooks()
{
    return requestAPI->getRequiredBooks();
}

void ViewRequiredBooksControl::launchAvailableItemWindow()
{
    QString user = requestAPI->getStudent()->getUsername();
    QUuid reqId = getRequiredBooks();

}

void ViewRequiredBooksControl::requiredBooksReceived(QUuid requestId, int code, QMap<Course*, QList<Textbook*>*>* cmap)
{
    qDebug() << "ViewRequiredBooksControl::requiredBooksReceived: Got response code " + QString::number(code) + " from server";

    // TODO Call request to get chapters and sections

    itemWindow = new AvailableItemWindow(0, requestAPI, cmap);

    QObject::connect(itemWindow, SIGNAL(availableItemWindowClosed()), this, SLOT(availableItemWindowClosed()));

    itemWindow->exec();
}

void ViewRequiredBooksControl::availableItemWindowClosed()
{
    delete itemWindow;
    qDebug() << "ViewRequiredBooksControl::AvailableItemWindowClosed: Deleted item window pointer";

    requestAPI = NULL;

    emit viewBooksControlFinished();
}
