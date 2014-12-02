#ifndef NETRESPONSE_H
#define NETRESPONSE_H

#include "NetMessage.h"

#include <QString>
#include <QDataStream>
#include <QUuid>

// FORMAT:  | (qint16) blockSize |
//          | (InvocationDescriptor->qint8) invocation |
//          | (QUuid) requestId |
//          | (QUuid) sessionId |
//          | (qint8) responseCode |
//          | (qint16) dataLen |
//          | (QByteArray) data |

class NetResponse : public NetMessage
{
public:
    NetResponse();

    // Returns string representation of this request
    virtual QString stringRepr() const;

    void setSessionId(QUuid sid);
    void setResponseCode(qint8 rc);

    QUuid getSessionId() const;
    qint8 getResponseCode() const;

    friend QDataStream& operator<<(QDataStream& os, const NetResponse& r); // output
    friend QDataStream& operator>>(QDataStream& is, NetResponse& r); // input

private:
    QUuid sessionId;
    qint8 responseCode;
};

#endif // NETRESPONSE_H
