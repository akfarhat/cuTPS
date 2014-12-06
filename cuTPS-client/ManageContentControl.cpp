#include "ManageContentControl.h"
#include "ContentManagementInterface.h"

#include <QDebug>

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

ManageContentControl::~ManageContentControl()
{
    delete contentManagementWin;
    delete requestAPI;
}

void ManageContentControl::addTextbook(QString name,
                                       int priceCents,
                                       bool isAvailable,
                                       QString isbn)
{
    qDebug() << "Adding new textbook " << name << " " << priceCents
             << ", available? " << isAvailable << " - " << isbn;

    // TODO: create AddTextbookControl with ContentRequestsAPI
    // to perform the request operation
}

void ManageContentControl::addChapter(QString name,
                                      int priceCents,
                                      bool isAvailable,
                                      int bookId)
{
    qDebug() << "Adding new chapter " << name << " " << priceCents
             << "to bookId = " << bookId << ", isAvailable? " << isAvailable;

    // TODO: create AddChapterControl with ContentRequestAPI
    // to handle the network request
}

void ManageContentControl::addSection(QString name,
                                      int priceCents,
                                      bool isAvailable,
                                      int chapterId)
{
    qDebug() << "Adding new section " << name << " " << priceCents
             << "to chapterId = " << chapterId << ", isAvailable? " << isAvailable;

    // TODO: create AddSectionControl with ContentRequestAPI
    // to handle the network request
}
