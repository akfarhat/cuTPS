// Class: Server
// Type: Control
// Description:
//     This class provides the server API for possible requests
//     for all user types in the cuTPS system. Most of these
//     requests will result in selecting from, or updating the database.

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "Utils.h"
#include "DatabaseManager.h"
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

    // Content Manager request API. Each of these requests
    // adds some content into the system availability

    ServerResponse addCourse(QUuid, Course);
    ServerResponse addTextbook(QUuid, Textbook);
    ServerResponse addChapter(QUuid, Chapter);
    ServerResponse addSection(QUuid, Section);

    // Student request API.

    // Get the list of required textbooks for a user
    ServerResponse getRequiredTextbooks(QUuid, const QString&);

    // Get the details for a particular textbook.
    // I.e. the sections and chapters that it contains,
    // as well as metadata
    ServerResponse getTextbookDetails(QUuid, int);

    // submit a student's order to the billing system
    ServerResponse submitOrder(QUuid, Order);

signals:

public slots:

private:
    QVector<QUuid> openSessions;
    DatabaseManager* dbManager;

private:
    bool generateSessionID(QUuid &, QString &);
    bool validateBillingInfo(BillingInfo *);
    bool validateDeliveryInfo(DeliveryInfo *);
    bool validateOrder(Order &, QString *);
};

#endif // SERVER_H
