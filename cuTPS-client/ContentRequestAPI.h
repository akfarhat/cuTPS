#ifndef CONTENTREQUESTAPI_H
#define CONTENTREQUESTAPI_H

#include <QObject>

#include "ClientNetworkHandler.h"

class ContentRequestAPI : public QObject
{
    Q_OBJECT

    public:
        explicit ContentRequestAPI(QObject *parent = 0, ClientNetworkHandler *net = NULL);

    signals:

    public slots:

    private:
        ClientNetworkHandler *networking;

};

#endif // CONTENTREQUESTAPI_H
