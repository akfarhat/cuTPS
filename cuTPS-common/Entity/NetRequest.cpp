#include "NetRequest.h"

NetRequest::NetRequest()
{
}

QString NetRequest::stringRepr() const
{
    return "[NetRequest(ID: " + getRequestId().toString()
            + ", Invo: " + QString::number((qint8) getInvocation())
            + ", DataSz: " + QString::number(getDataSize()) + ")]";
}

QDataStream& operator<<(QDataStream& os, const NetRequest& r)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    qint8 invocationInteger = static_cast<qint8>(r.invocation);

    // Do not change the sequence!
    os << (qint16) 0;
    os << TPSNetProtocolDef::PROTOCOL_MAGIC;
    os << invocationInteger;
    os << r.requestId;

    qint32 rDataSz = r.getDataSize();
    os << rDataSz;

    if (rDataSz) {
        os << *r.data;
    }

    os.device()->seek(0);
    // Requests consist of invocation integer (qint8), req.id (QUUid)
    // dataSize (qint16) + extra data itself (as rqDataSize)!

    qint16 blockSz = sizeof(qint8)    // invocation
            + sizeof(QUuid)           // requestId
            + 2*sizeof(qint32)        // dataSize + magic
            + rDataSz;                // data

    os << blockSz;

    return os;
}

QDataStream& operator>>(QDataStream& is, NetRequest& r)
{
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    qint8 invocationInteger;
    QUuid requestId;
    qint32 dataSz, magicCheck;

    is >> magicCheck;

    if (magicCheck != TPSNetProtocolDef::PROTOCOL_MAGIC)
        throw NetMessage::BadRequestException();

    is >> invocationInteger
            >> requestId
            >> dataSz;

    r.setInvocation(static_cast<TPSNetProtocolDef::InvocationDescriptor>(invocationInteger));
    r.setRequestId(requestId);

    if (dataSz > 0) {
        r.clearData();
        QByteArray bytes;
        bytes.resize(dataSz);
        is >> bytes;
        r.setData(bytes);
    }

    return is;
}
