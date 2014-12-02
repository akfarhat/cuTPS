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
    os.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    qint8 invocationInteger = static_cast<qint8>(r.invocation);

    // Do not change the sequence!
    os << (qint16) 0;
    os << invocationInteger;
    os << r.requestId;

    qint16 rqDataSize = r.getDataSize();

    if (r.hasExtraData()) {
        os << rqDataSize;
        os << *(r.data);
    } else {
        rqDataSize = 0; // it's already must be 0, setting it here just to be sure
        os << rqDataSize;
    }

    os.device()->seek(0);
    // Requests consist of invocation integer (qint8), req.id (QUUid)
    // dataSize (qint16) + extra data itself (as rqDataSize)!
    qint16 blockSz = (quint16)(rqDataSize + sizeof(qint8) + sizeof(QUuid) + sizeof(qint16));
    os << blockSz;

    return os;
}

QDataStream& operator>>(QDataStream& is, NetRequest& r)
{
    is.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    qint8 invocationInteger;
    QUuid requestId;
    qint16 dataSz;

    is >> invocationInteger
        >> requestId
        >> dataSz;

    r.setInvocation(static_cast<TPSNetProtocolDefs::InvocationDescriptor>(invocationInteger));
    r.setRequestId(requestId);

    if (dataSz > 0) {
        r.clearData();
        QByteArray bytes;
        is >> bytes;
        r.setData(bytes);
    }

    return is;
}
