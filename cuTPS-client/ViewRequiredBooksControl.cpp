#include "ViewRequiredBooksControl.h"

ViewRequiredBooksControl::ViewRequiredBooksControl(CartRequestsAPI *api)
    : requestAPI(api)
{
    itemWindow = NULL;

    QObject::connect(requestAPI->getNetwork(), SIGNAL(textbookLookupCompleted(QUuid, int, QVector<qint32> *)), this, SLOT(textbookLookupCompleted(QUuid, int, QVector<qint32> *)));
    QObject::connect(requestAPI->getNetwork(), SIGNAL(textbookDetailsReceived(QUuid, int, QVector<Textbook *> *)), this, SLOT(textbookDetailsReceived(QUuid, int, QVector<Textbook *> *)));


}

ViewRequiredBooksControl::~ViewRequiredBooksControl()
{
    requestAPI = NULL;
}

QUuid ViewRequiredBooksControl::getRequiredBooks(QString& username)
{
    return requestAPI->getRequiredBooks(username);
}

QUuid ViewRequiredBooksControl::getBookDetails(const QVector<qint32> &ids)
{
    return requestAPI->getBookDetails(ids);
}

void ViewRequiredBooksControl::textbookLookupCompleted(QUuid requestId, int code, QVector<qint32> *booksIds)
{
    qDebug() << "ViewRequiredBooksControl::textbookLookupCompleted: Got response code " + QString::number(code) + " from server";

    if (code == ResponseCode::Success) {
        if (!booksIds->empty()) {
            getBookDetails(*booksIds);
        }
    }
}

void ViewRequiredBooksControl::textbookDetailsReceived(QUuid requestId, int code, QVector<Textbook *> *books)
{
    qDebug() << "ViewRequiredBooksControl::textbookDetailsReceived: Got response code " + QString::number(code) + " from server";

    // TODO Call request to get chapters and sections

    itemWindow = new AvailableItemWindow(0, requestAPI, books);

    QObject::connect(itemWindow, SIGNAL(availableItemWindowClosed()), this, SLOT(availableItemWindowClosed()));

    itemWindow->exec();
}

void ViewRequiredBooksControl::launchAvailableItemWindow()
{
    QString user = requestAPI->getStudent()->getUsername();
    QUuid reqId = getRequiredBooks(user);

}


void ViewRequiredBooksControl::availableItemWindowClosed()
{
    delete itemWindow;
    qDebug() << "ViewRequiredBooksControl::AvailableItemWindowClosed: Deleted item window pointer";

    requestAPI = NULL;

    emit viewBooksControlFinished();
}
