#ifndef TPSCLIENT_H
#define TPSCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include "TPSWorkerTask.h"

class TPSClient : public QObject
{
    Q_OBJECT
public:
    explicit TPSClient(QObject *parent = 0);
    void SetSocket(qintptr sockdescriptor);
signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void taskResult(int code);

private:
    QTcpSocket *socket;
};

#endif // TPSCLIENT_H
