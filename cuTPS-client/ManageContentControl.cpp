#include "ManageContentControl.h"
#include "ContentManagementInterface.h"
#include "AddBookControl.h"
#include "ModifyItemControl.h"
#include "DeleteItemControl.h"

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

    QUuid reqId;

    Textbook book(bookId, name, "", "", priceCents, isAvailable, isbn);

    if (bookId == -1) {
        AddBookControl addBookCtrl(this->requestAPI);

        // TODO: we currently ignore response for this request
        addBookCtrl.addBook(reqId, book);
    } else {
        ModifyItemControl modCtrl(0, this->requestAPI);

        // TODO: not currently handling response
        modCtrl.modifyBook(reqId, book);
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

    QUuid reqId;

    Chapter chapter(NULL, chapId, name, priceCents, isAvailable);

    if (chapId == -1) {
        AddBookControl addBookCtrl(this->requestAPI);

        // TODO: we currently ignore response for this request
        addBookCtrl.addChapter(reqId, bookId, chapter);
    } else {
        ModifyItemControl modCtrl(0, this->requestAPI);

        // TODO: curently ignoring response
        modCtrl.modifyChapter(reqId, bookId, chapter);
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

    QUuid reqId;

    Section section(NULL, secId, name, priceCents, isAvailable);

    if (secId == -1) {
        AddBookControl addBookCtrl(this->requestAPI);

        // TODO: we currently ignore response for this request
        addBookCtrl.addSection(reqId, bookId, chapterId, section);
    } else {
        ModifyItemControl modCtrl(0, this->requestAPI);

        // TODO: not currently handling response
        modCtrl.modifySection(reqId, bookId, chapterId, section);
    }
}

void ManageContentControl::deleteItem(int itemId)
{
    qDebug() << "Deleting item id " << itemId;

    DeleteItemControl ctrl(this->requestAPI);

    // TODO: not yet handling response
    QUuid uid;
    ctrl.deleteItem(uid, itemId);
}
