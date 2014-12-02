#ifndef NETMESSAGE_H
#define NETMESSAGE_H

#include <QUuid>
#include <QByteArray>
#include <QString>

#include "Defines.h"

class NetMessage
{
public:
    NetMessage();
    virtual ~NetMessage();

    void    setRequestId(QUuid id);
    void    setInvocation(TPSNetProtocolDefs::InvocationDescriptor invo);

    QUuid   getRequestId() const;
    TPSNetProtocolDefs::InvocationDescriptor getInvocation() const;

    QByteArray*     getData();  // nullptr is returned if data not present
    void            setData(const QByteArray& data); // copy-on-write enabled. (fast!)
    void            setRawData(const char* rawData, int len); // makes deep copy of rawData
    bool            hasExtraData() const; // returns false if getDataSize == 0, true otherwise
    int             getDataSize() const; // 0 if no data is present
    void            clearData();  // erases any present data

    virtual QString stringRepr() const = 0;

protected:
    // Every NetMessage is identified by a unique ID.
    QUuid requestId;

    // Identifies the action to be performed for this request message, or the action
    // that has been performed for this response message.
    TPSNetProtocolDefs::InvocationDescriptor invocation;

    // Holds any extra data to parametrize the request or provide response data.
    QByteArray* data = nullptr;
};

#endif // NETMESSAGE_H
