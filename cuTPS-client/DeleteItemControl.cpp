#include "DeleteItemControl.h"

DeleteItemControl::DeleteItemControl(QObject *parent, ContentRequestAPI *api) :
    QObject(parent),
    requestAPI(api)
{
}

void DeleteItemControl::deleteItem(QUuid &uid, int itemId)
{
    uid = requestAPI->deleteItem(itemId);
}
