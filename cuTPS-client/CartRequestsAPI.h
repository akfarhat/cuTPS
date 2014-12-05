// Class: CartRequestsAPI
// Type: Control
// Description:
//     this class is responsible for invoking cart-related requests to the client network handler.
//
// Traceability: CartRequestsAPI class in the CartManagement subsystem

#ifndef CARTREQUESTSAPI_H
#define CARTREQUESTSAPI_H

#include <QObject>
#include <QUuid>
#include "ClientNetworkHandler.h"
#include "Entity/Textbook.h"
#include "Entity/Order.h"
#include "Entity/Student.h"

class CartRequestsAPI: public QObject {
    Q_OBJECT

    public:
        explicit CartRequestsAPI(QObject *parent = 0, ClientNetworkHandler *net = NULL, Student *stu = NULL);
        ~CartRequestsAPI();

        QUuid getRequiredBooks(QString&);
        QUuid getBookDetails(int bookId);
        QUuid submitOrder(Order&);

        Student* getStudent();

        ClientNetworkHandler* getNetwork();

    private:
        ClientNetworkHandler *network;
        Student *student;


};

#endif // CARTREQUESTSAPI_H
