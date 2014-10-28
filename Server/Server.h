#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QString>

#include "Utils.h"
#include "Entity/Course.h"
#include "Entity/Textbook.h"
#include "Entity/Order.h"
#include "Entity/Chapter.h"
#include "Entity/Section.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();

    //createSession() must be called first to establish a session,
    // it returns a ServerResponse struct which contains a sessionID
    ServerResponse createSession();

    //All Server API functions except createSession() take sessionID
    // as the first parameter

    // All Users
    ServerResponse authenticateUser(int, UserCredentials);

    // Content Managers
    ServerResponse addCourse(int, Course);
    ServerResponse addTextbook(int, Textbook);
    ServerResponse addChapter(int, Chapter);
    ServerResponse addSection(int, Section);

    // Students
    ServerResponse getRequiredTextbooks(int, int);
    ServerResponse getTextbookDetails(int, int);
    ServerResponse submitOrder(int, Order);

signals:

public slots:

};

#endif // SERVER_H
