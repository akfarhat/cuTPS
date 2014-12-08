#include "ContentRequestAPI.h"

ContentRequestAPI::ContentRequestAPI(QObject *parent, ClientNetworkHandler *net) :
    QObject(parent)
{
    this->networking = net;
}
