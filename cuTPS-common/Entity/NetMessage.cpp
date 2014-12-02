#include "NetMessage.h"

NetMessage::NetMessage()
{
}

NetMessage::~NetMessage()
{
    if (data) {
        delete data;
    }
}

void NetMessage::setRequestId(QUuid id)
{
    requestId = id;
}

void NetMessage::setInvocation(TPSNetProtocolDefs::InvocationDescriptor invo)
{
    invocation = invo;
}

bool NetMessage::hasExtraData() const
{
    if (data) {
        return !data->isEmpty();
    } else {
        return false;
    }
}

QUuid NetMessage::getRequestId() const
{
    return requestId;
}

TPSNetProtocolDefs::InvocationDescriptor NetMessage::getInvocation() const
{
    return invocation;
}

QByteArray* NetMessage::getData()
{
    return data;
}

int NetMessage::getDataSize() const
{
    if (!hasExtraData())
        return 0;
    else
        return data->size();
}

void NetMessage::setData(const QByteArray& newData)
{
    if (data)
        delete data; // delete old data if present

    data = new QByteArray(newData); // allocate a copy of new data
}

void NetMessage::setRawData(const char *rawData, int len)
{
    if (data)
        delete data;

    data = new QByteArray(rawData, len);
}

void NetMessage::clearData()
{
    if (data)
        data->clear();
}
