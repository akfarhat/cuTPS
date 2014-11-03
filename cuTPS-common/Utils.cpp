#include "Utils.h"

#include <QDataStream>

#include "Defines.h"

void TPSNetUtils::SerializeRequest(QDataStream* ostream, const TPSNetProtocol::NetRequest* rq)
{
    ostream->setVersion(TPSConstants::PROTOCOL_VER);

    qint8 invocationInteger = static_cast<qint8>(rq->invocation);

    // Do not change the sequence!
    *ostream << (qint16) 0;
    *ostream << invocationInteger;
    *ostream << rq->requestId;
    *ostream << *(rq->data);

    (*ostream).device()->seek(0);
    *ostream << (quint16)(rq->data->size() + sizeof(quint8) + sizeof(QUuid));
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
    *ostream << *(rq->data);

    (*ostream).device()->seek(0);
    *ostream << (quint16)(rq->data->size() + (2*sizeof(quint8)) + (2*sizeof(QUuid)));
}

void TPSNetUtils::DeserializeRequest(TPSNetProtocol::NetRequest* dest, QDataStream* src)
{
    qint8 invocationInteger;
    (*src) >> dest->blockSize;
    (*src) >> invocationInteger;
    dest->invocation = static_cast<TPSConstants::InvocationDescriptor>(invocationInteger);
    (*src) >> dest->requestId;
    (*src) >> *(dest->data);
}

void TPSNetUtils::DeserializeResponse(TPSNetProtocol::NetResponse* dest, QDataStream* src)
{
    qint8 invocationInteger;
    (*src) >> dest->blockSize;
    (*src) >> invocationInteger;
    dest->invocation = static_cast<TPSConstants::InvocationDescriptor>(invocationInteger);
    (*src) >> dest->requestId;
    (*src) >> dest->sessionId;
    (*src) >> dest->responseCode;
    (*src) >> *(dest->data);
}
