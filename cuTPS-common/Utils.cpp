#include "Utils.h"

#include <QDataStream>
#include <QDebug>

#include "Defines.h"

void TPSNetUtils::SerializeRequest(QDataStream* ostream, const TPSNetProtocol::NetRequest* rq)
{
    ostream->setVersion(TPSConstants::PROTOCOL_VER);

    qint8 invocationInteger = ((qint8)rq->invocation);
    // Do not change the sequence!
    *ostream << (qint16) 0;
    *ostream << invocationInteger;
    *ostream << rq->requestId;
    qint16 rqDataSize = rq->data->size();
    *ostream << *(rq->data);

    (*ostream).device()->seek(0);
    qint16 blockSz = (quint16)(rqDataSize + sizeof(quint8) + sizeof(QUuid));
    *ostream << blockSz;
}

void TPSNetUtils::SerializeResponse(QDataStream* ostream, const TPSNetProtocol::NetResponse* rq)
{
    ostream->setVersion(TPSConstants::PROTOCOL_VER);

    qint8 invocationInteger = static_cast<qint8>(rq->invocation);

    // Do not change the sequence!
    *ostream << (qint16) 0;
    *ostream << invocationInteger;
    *ostream << rq->requestId;
    *ostream << rq->sessionId;
    *ostream << rq->responseCode;

    qint16 rqDataSize = rq->data->size();
    *ostream << *(rq->data);

    (*ostream).device()->seek(0);
    qint16 blockSz = (quint16)(rqDataSize + (2*sizeof(quint8)) + (2*sizeof(QUuid)));
    *ostream << blockSz;
}

void TPSNetUtils::DeserializeRequest(TPSNetProtocol::NetRequest* dest, QDataStream* src)
{
    qint8 invocationInteger;
    QUuid requestId;
    QByteArray* dataBlock = dest->data;

    (*src) >> invocationInteger >> requestId >> (*dataBlock);

    dest->invocation = static_cast<TPSConstants::InvocationDescriptor>(invocationInteger);
    dest->requestId = requestId;
}

void TPSNetUtils::DeserializeResponse(TPSNetProtocol::NetResponse* dest, QDataStream* src)
{
    qint8 invocationInteger;
    QUuid requestId;
    QUuid sessionId;
    qint8 responseCode;
    QByteArray* dataBlock = dest->data;

    (*src) >> invocationInteger
            >> requestId
            >> sessionId
            >> responseCode
            >> (*dataBlock);

    dest->invocation = static_cast<TPSConstants::InvocationDescriptor>(invocationInteger);
    dest->requestId = requestId;
    dest->sessionId = sessionId;
    dest->responseCode = responseCode;
}
