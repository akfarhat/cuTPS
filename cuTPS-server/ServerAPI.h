#ifndef SERVERAPI_H
#define SERVERAPI_H

#include <QObject>

class ServerAPI : public QObject
{
    Q_OBJECT
public:
    explicit ServerAPI(QObject *parent = 0);

signals:

public slots:

};

#endif // SERVERAPI_H
