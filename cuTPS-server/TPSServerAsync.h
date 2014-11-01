#ifndef TPSSERVERASYNC_H
#define TPSSERVERASYNC_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include "TPSClient.h"

#define PORT 17251 // BAD: TODO: Make it dynamic instead

class TPSServerAsync : public QTcpServer
{
    Q_OBJECT
public:
    explicit TPSServerAsync(QObject *parent = 0);
    void StartServer();

protected:

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    void incomingConnection(int handle);
#else
    void incomingConnection(qintptr handle);
#endif

signals:

public slots:

};

#endif // TPSSERVERASYNC_H
