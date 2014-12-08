#include "DeleteItemControl.h"

DeleteItemControl::DeleteItemControl(QObject *parent, ContentRequestAPI *api) :
    QObject(parent),
    requestAPI(api)
{
}

void DeleteItemControl::deleteItem(QUuid &uid, int itemId, QString type)
{
    // This could be changed into one API request if the server
    // implementation was updated.

    if (type == "textbook")
        uid = requestAPI->deleteTextbook(itemId);
    else if (type == "chapter")
        uid = requestAPI->deleteChapter(itemId);
    else if (type == "section")
        uid = requestAPI->deleteSection(itemId);
}
