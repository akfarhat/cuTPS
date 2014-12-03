#include "CourseRequestAPI.h"

CourseRequestAPI::CourseRequestAPI(QObject *parent,
                                   ClientNetworkHandler *net) :
    QObject(parent)
{
    this->networking = net;
}
