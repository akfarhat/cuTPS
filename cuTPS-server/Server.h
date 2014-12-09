// Class: Server
// Type: Control
// Description:
//     This class provides the server API for possible requests
//     for all user types in the cuTPS system. Most of these
//     requests will result in selecting from, or updating the database.

#ifndef SERVER_H
#define SERVER_H

#include <memory>

#include <QObject>
#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "Defines.h"
#include "DatabaseManager.h"
#include "Entity/Course.h"
#include "Entity/Textbook.h"
#include "Entity/Order.h"
#include "Entity/Chapter.h"
#include "Entity/Section.h"
#include "Entity/Student.h"

using namespace TPSDef;

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

    //closeSession() takes in a sessionID and removes it from the openSessions
    ServerResponse closeSession(QUuid);

    //All Server API functions except createSession() take sessionID
    // as the first parameter

    // All Users
    ServerResponse authenticateUser(QUuid, Role&, UserCredentials);
    ServerResponse getSessionRole(QUuid, Role&);
    ServerResponse getSessionUserId(QUuid, int&);

    // Content Manager request API. Each of these requests
    // adds some content into the system availability

    // TODO: make server return ids for created items (i.e. set newId)
    ServerResponse addCourse(QUuid, Course&, qint32& newId);
    ServerResponse addTextbook(QUuid, Textbook&, qint32& newId);
    ServerResponse addChapter(QUuid, Chapter&, qint32& newId);
    ServerResponse addSection(QUuid, Section&, qint32& newId);

    ServerResponse replaceCourse(QUuid, qint32 id, Course&);
    ServerResponse replaceTextbook(QUuid, qint32 id, Textbook&);
    ServerResponse replaceChapter(QUuid, qint32 id, Chapter&);
    ServerResponse replaceSection(QUuid, qint32 id, Section&);

    ServerResponse removeCourse(QUuid, qint32 id);
    ServerResponse removeSellableItem(QUuid, qint32 id);

    ServerResponse registerStudentUser(QUuid, Student& usr, QString pwd, qint32* id);

    ServerResponse getAllTextbooks(QUuid, QVector<Textbook>&);
    ServerResponse getAllCourses(QUuid, QVector<Course>&);

    // Student request API.

    // Get the list of courses a student is registered in
    ServerResponse getStudentCourses(QUuid, const int&, QVector<Course>&);

    // Get the list of required textbooks for a user
    ServerResponse getRequiredTextbooks(QUuid, const int&, QVector<int>*);

    // Get the metadata for a sellable item
    ServerResponse getItemDetails(QUuid, int);

    // Get the metadata for a particular textbook
    // TODO: decide if we want to revert book arg to std::unique_ptr<Textbook>*
    // changing it for now for simplicity while debugging.
    ServerResponse getTextbookDetails(QUuid, int, Textbook**);

    // Get a list of chapter and section objects in a particular textbook
    ServerResponse getTextbookParts(QUuid, int, QVector<SellableItem*>*);

    // submit a student's order to the billing system
    ServerResponse submitOrder(QUuid, Order);

signals:

public slots:

private:
    QMap<QUuid, int> openSessions;
    DatabaseManager* dbManager;

private:
    bool generateSessionID(QUuid &, QString &);
    bool validateBillingInfo(const BillingInfo *);
    bool validateDeliveryInfo(const DeliveryInfo *);
    bool validateOrder(Order &, QString *);
    Role getUserRole(QString &);
};

#endif // SERVER_H
