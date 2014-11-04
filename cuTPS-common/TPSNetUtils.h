#ifndef TPSNETUTILS_H
#define TPSNETUTILS_H

#include <QDataStream>

#include "Utils.h"
#include "Entity/Textbook.h"
#include "Entity/Course.h"
#include "Entity/Order.h"

class TPSNetUtils {
public:
    static void SerializeRequest(QDataStream* dest, const TPSNetProtocol::NetRequest* src);
    static void SerializeResponse(QDataStream* dest, const TPSNetProtocol::NetResponse* src);
    static void DeserializeRequest(TPSNetProtocol::NetRequest* dest, QDataStream* src);
    static void DeserializeResponse(TPSNetProtocol::NetResponse* dest, QDataStream* src);

    static void SerializeTextbook(QDataStream* dest, const Textbook* src);
    static void DeserializeTextbook(Textbook* dest, QDataStream* src);

    static void SerializeCourse(QDataStream* dest, const Course* src);
    static void DeserializeCourse(Course* dest, QDataStream* src);

    static void SerializeOrder(QDataStream* dest, Order* src);
    static void DeserializeOrder(Order* dest, QDataStream* src);

protected:
    virtual void getNothing(void) = 0; // C++ is a perfect language
};

#endif // TPSNETUTILS_H
