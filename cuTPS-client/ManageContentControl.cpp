#include "ManageContentControl.h"
#include "ContentManagementInterface.h"
#include "AddBookControl.h"

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

    connect(contentManagementWin, SIGNAL(deleteItem(int)),
            this, SLOT(deleteItem(int)));
    // TODO: connect slots for requests that the networking will signal
}

ManageContentControl::~ManageContentControl()
{
    delete contentManagementWin;
    delete requestAPI;
}

void ManageContentControl::addTextbook(QString name,
                                       int bookId,
                                       int priceCents,
                                       bool isAvailable,
                                       QString isbn)
{
    qDebug() << "Add/modify textbook " << name << ", id=" << bookId
             << " " << priceCents << ", available? "
             << isAvailable << " - " << isbn;

    AddBookControl addBookCtrl(this->requestAPI);

    QUuid reqId;

    if (bookId == -1) {
        Textbook book(0, name, "", "", priceCents, isAvailable, isbn);

        // TODO: we currently ignore response for this request
        addBookCtrl.addBook(reqId, book);
    } else {
        // TODO: create a modifyBookCtrl...
    }
}

void ManageContentControl::addChapter(QString name,
                                      int chapId,
                                      int priceCents,
                                      bool isAvailable,
                                      int bookId)
{
    qDebug() << "Add/modify chapter " << name << ", id=" << chapId
             << " " << priceCents << "to bookId = " << bookId
             << ", isAvailable? " << isAvailable;

    AddBookControl addBookCtrl(this->requestAPI);

    QUuid reqId;

    if (chapId == -1) {
        Chapter chapter(NULL, 0, name, priceCents, isAvailable);

        // TODO: we currently ignore response for this request
        addBookCtrl.addChapter(reqId, bookId, chapter);
    } else {
        // TODO: create a modifyBookCtrl..
    }
}

void ManageContentControl::addSection(QString name,
                                      int secId,
                                      int priceCents,
                                      bool isAvailable,
                                      int bookId,
                                      int chapterId)
{
    qDebug() << "Add/modify section " << name << ", id=" << secId
             << " " << priceCents << "to chapterId = " << chapterId
             << "and bookId = " << bookId << ", isAvailable? " << isAvailable;

    AddBookControl addBookCtrl(this->requestAPI);

    QUuid reqId;

    if (secId == -1) {
        Section section(NULL, 0, name, priceCents, isAvailable);

        // TODO: we currently ignore response for this request
        addBookCtrl.addSection(reqId, bookId, chapterId, section);
    } else {
        // TODO: create a modifyBookControl...
    }
}

void ManageContentControl::deleteItem(int itemId)
{
    qDebug() << "Deleting item id " << itemId;

    // TODO: create a DeleteItemControl with the requestAPI
}
