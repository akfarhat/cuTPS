#ifndef NETREQUEST_H
#define NETREQUEST_H

#include "NetMessage.h"

#include <QString>
#include <QDataStream>

// FORMAT:  | (qint16) blockSize |
//          | (InvocationDescriptor) invocation |
//          | (QUuid) requestId |
//          | (qint16) dataLen |
//          | (QByteArray) data |

class NetRequest : public NetMessage
{
public:
    NetRequest();

    // Returns string representation of this request
    virtual QString stringRepr() const;

    friend QDataStream& operator<<(QDataStream& os, const NetRequest& r); // output
    friend QDataStream& operator>>(QDataStream& is, NetRequest& r); // input
};

#endif // NETREQUEST_H
