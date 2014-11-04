#include "TPSNetUtils.h"

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

void TPSNetUtils::DeserializeRequest(TPSNetProtocol::NetRequest* dest, QDataStream* istream)
{
    qint8 invocationInteger;
    QUuid requestId;
    QByteArray* dataBlock = dest->data;

    (*istream) >> invocationInteger
            >> requestId
             >> (*dataBlock);

    dest->invocation = static_cast<TPSConstants::InvocationDescriptor>(invocationInteger);
    dest->requestId = requestId;
}

void TPSNetUtils::DeserializeResponse(TPSNetProtocol::NetResponse* dest, QDataStream* istream)
{
    qint8 invocationInteger;
    QUuid requestId;
    QUuid sessionId;
    qint8 responseCode;
    QByteArray* dataBlock = dest->data;

    (*istream) >> invocationInteger
            >> requestId
            >> sessionId
            >> responseCode
            >> (*dataBlock);

    dest->invocation = static_cast<TPSConstants::InvocationDescriptor>(invocationInteger);
    dest->requestId = requestId;
    dest->sessionId = sessionId;
    dest->responseCode = responseCode;
}

void TPSNetUtils::SerializeTextbook(QDataStream* ostream, const Textbook* src)
{
    (*ostream) << (qint32) src->getId()
               << src->getName()
               << src->getISBN()
               << (qint32) src->getPriceCents()
               << src->getAvailability();
}

void TPSNetUtils::DeserializeTextbook(Textbook* dest, QDataStream* istream)
{
    qint32 id;
    QString name;
    QString isbn;
    qint32 price;
    bool isAvailable;

    (*istream) >> id >> name >> isbn >> price >> isAvailable;

    dest->setId(id);
    dest->setName(name);
    dest->setISBN(isbn);
    dest->setPriceCents(price);
    dest->setAvailability(isAvailable);
}

void TPSNetUtils::SerializeCourse(QDataStream* ostream, const Course* src)
{
    (*ostream) << (qint32) src->getId()
               << src->getCourseName()
               << src->getCourseCode()
               << (qint32) src->getRequiredTexts()->size();

    for (int i = 0; i < src->getRequiredTexts()->size(); ++i)
    {
        Textbook* book = (*(src->getRequiredTexts()))[i];
        (*ostream) << (qint32) book->getId();
    }
}

void TPSNetUtils::DeserializeCourse(Course* dest, QDataStream* istream)
{
    qint32 id;
    QString name;
    QString code;
    qint32 numLinkedBooks;

    (*istream) >> id >> name >> code >> numLinkedBooks;

    qint32 bookIds[numLinkedBooks];
    QVector<Textbook*>* books = dest->getRequiredTexts();

    for (int i = 0; i < numLinkedBooks; ++i)
    {
        // TODO: Fetch textbooks by ID and add to the vector
    }

    dest->setId(id);
    dest->setCourseName(name);
    dest->setCourseCode(code);
}

void TPSNetUtils::SerializeOrder(QDataStream* ostream, Order* src)
{
    QVector<qint32> vec;
    qint32 numItems = src->getOrder()->size();

    (*ostream) << src->getBillingInfo()->getName()
               << src->getBillingInfo()->getEmail()
               << src->getBillingInfo()->getBillingAddress()
               << src->getBillingInfo()->getPhoneNumber()
               << src->getDeliveryInfo()->getEmailAddress()
               << numItems;

    for (int i = 0; i < numItems; ++i)
    {
        (*ostream) << (*(src->getOrder())).at(i);
    }
}

void TPSNetUtils::DeserializeOrder(Order* dest, QDataStream* istream)
{
    // read order
    qint32 numItems = 0;
    QString name, bEmail, bAddress, phoneNum, dEmail;

    (*istream) >> name
            >> bEmail
            >> bAddress
            >> phoneNum
            >> dEmail
            >> numItems;

    QVector<qint32>* vec = dest->getOrder();

    for (int i = 0; i < numItems; ++i)
    {
        int id;
        (*istream) >> id;
        vec->append(id);
    }
}
