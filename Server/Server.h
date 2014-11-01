#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "Utils.h"
#include "Server/DatabaseManager.h"
#include "Entity/Course.h"
#include "Entity/Textbook.h"
#include "Entity/Order.h"
#include "Entity/Chapter.h"
#include "Entity/Section.h"

class Server : public QObject
{
    Q_OBJECT
public:
    static const int MAX_SESSIONS = 10;

public:
    explicit Server(QObject *parent = 0);
    ~Server();

    //createSession() must be called first to establish a session,
    // it returns a ServerResponse struct which contains a sessionID
    // and a return code
    ServerResponse createSession();

    //All Server API functions except createSession() take sessionID
    // as the first parameter

    // All Users
    ServerResponse authenticateUser(QUuid, UserCredentials);

    // Content Managers
    ServerResponse addCourse(QUuid, Course);
    ServerResponse addTextbook(QUuid, Textbook);
    ServerResponse addChapter(QUuid, Chapter);
    ServerResponse addSection(QUuid, Section);

    // Students
    ServerResponse getRequiredTextbooks(QUuid, int);
    ServerResponse getTextbookDetails(QUuid, int);
    ServerResponse submitOrder(QUuid, Order);

signals:

public slots:

private:
    QVector<QUuid> openSessions;
    DatabaseManager* dbManager;

private:
    bool generateSessionID(QUuid&, QString&);
    bool validateOrder(Order&, QString&);
};

#endif // SERVER_H
