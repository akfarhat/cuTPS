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
    void incomingConnection(qintptr handle);

signals:

public slots:

};

#endif // TPSSERVERASYNC_H
