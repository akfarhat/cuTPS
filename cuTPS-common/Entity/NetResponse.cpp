#include "NetResponse.h"

NetResponse::NetResponse()
{
}

NetResponse::NetResponse(NetMessage& m)
{
    this->setRequestId(m.getRequestId());
    this->setInvocation(m.getInvocation());
}

QString NetResponse::stringRepr() const
{
    return "[NetResponse (ID: " + getRequestId().toString()
           + ", Invocation: " + QString::number((qint8) getInvocation())
           + ", Session ID: " + getSessionId().toString()
           + ", Response code: " + QString::number(getResponseCode())
           + ", DataSz: " + QString::number(getDataSize()) + ")]";
}

void NetResponse::setSessionId(QUuid sid)
{
    sessionId = sid;
}

void NetResponse::setResponseCode(qint8 rc)
{
    responseCode = rc;
}

QUuid NetResponse::getSessionId() const
{
    return sessionId;
}

qint8 NetResponse::getResponseCode() const
{
    return responseCode;
}

QDataStream& operator<<(QDataStream& os, const NetResponse& r)
{
    os.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    qint8 invocationInteger = static_cast<qint8>(r.invocation);

    // Do not change the sequence!
    os << (qint16) 0;
    os << TPSNetProtocolDefs::PROTOCOL_MAGIC;
    os << invocationInteger;
    os << r.requestId;
    os << r.sessionId;
    os << r.responseCode;

    qint16 rqDataSize = r.getDataSize();

    if (r.hasExtraData()) {
        os << rqDataSize;
        os << *(r.data);
    } else {
        rqDataSize = 0; // it's already must be 0, setting it here just to be sure
        os << rqDataSize;
    }

    os.device()->seek(0);
    // Requests consist of invocation integer + response code (2*qint8),
    // requestId + sessionId (2*QUUid), dataSize (qint16) + extra data itself.
    qint16 blockSz = rqDataSize + 2*sizeof(qint8) + 2*sizeof(QUuid) + sizeof(qint16) + sizeof(qint32);
    os << blockSz;

    return os;
}

QDataStream& operator>>(QDataStream& is, NetResponse& r)
{
    is.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    qint8 invocationInteger, responseCode;
    QUuid requestId, sessionId;
    qint16 dataSz;

    is >> invocationInteger
        >> requestId
        >> sessionId
        >> responseCode
        >> dataSz;

    r.setInvocation(static_cast<TPSNetProtocolDefs::InvocationDescriptor>(invocationInteger));
    r.setRequestId(requestId);
    r.setSessionId(sessionId);
    r.setResponseCode(responseCode);

    if (dataSz > 0) {
        r.clearData();
        QByteArray bytes;
        is >> bytes;
        r.setData(bytes);
    }

    return is;
}
