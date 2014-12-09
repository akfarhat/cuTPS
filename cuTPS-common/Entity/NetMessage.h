#ifndef NETMESSAGE_H
#define NETMESSAGE_H

#include "libcutps_global.h"

#include <QUuid>
#include <QByteArray>
#include <QString>
#include <exception>

#include "Defines.h"

class LIBCUTPS_EXPORT NetMessage
{
public:
    NetMessage();
    virtual ~NetMessage();

    void    setRequestId(QUuid id);
    void    setInvocation(TPSNetProtocolDef::InvocationDescriptor invo);

    QUuid   getRequestId() const;
    TPSNetProtocolDef::InvocationDescriptor getInvocation() const;

    QByteArray*     getData();  // nullptr is returned if data not present
    void            setData(const QByteArray& data); // copy-on-write enabled. (fast!)
    void            setRawData(const char* rawData, int len); // makes deep copy of rawData
    bool            hasExtraData() const; // returns false if getDataSize == 0, true otherwise
    int             getDataSize() const; // 0 if no data is present
    void            clearData();  // erases any present data

    virtual QString stringRepr() const = 0;

    class BadRequestException : public std::exception
    {
    public:
        virtual const char* what() const throw()
        {
          return "Bad data received from host";
        }
    };

protected:
    // Every NetMessage is identified by a unique ID.
    QUuid requestId;

    // Identifies the action to be performed for this request message, or the action
    // that has been performed for this response message.
    TPSNetProtocolDef::InvocationDescriptor invocation;

    // Holds any extra data to parametrize the request or provide response data.
    QByteArray* data;
};




#endif // NETMESSAGE_H
