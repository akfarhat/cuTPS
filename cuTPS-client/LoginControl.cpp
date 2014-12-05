#include "LoginControl.h"
#include "ContentManagementInterface.h"

#include <QDebug>

#include "Entity/Chapter.h"
#include "Entity/Section.h"
#include "Entity/CreditcardInfo.h"

LoginControl::LoginControl(ClientNetworkHandler *serverAPI)
    : network(serverAPI)
{
    // Connect handlers for network callbacks on login events
    connect(network, SIGNAL(loginSuccessful(QUuid, Role)),
            this, SLOT(loginSuccessful(QUuid, Role)));

    connect(network, SIGNAL(loginFailed(QUuid)),
            this, SLOT(loginFailed(QUuid)));
}

LoginControl::~LoginControl() {
}

void LoginControl::startSession()
{
    // Create the login window with this as its parent
    loginWin = new Login(0, network, this);

    loginWin->show();
}

void LoginControl::login(QUuid &reqId, UserCredentials &userCreds) {
    reqId = network->login(userCreds);
}

void LoginControl::loginSuccessful(QUuid requestId, Role userRole) {
    qDebug() << "LoginControl::successfulLogin for: " << userRole
             << " - " << requestId;

    // TODO: Need to get user information such as name, etc. from DB to create the user (i.e. Student or ContentManager) object that will be passed around
    switch (userRole) {

        case Role::StudentUser:
          {
            qDebug() << "LoginControl::loginSuccessful creating studentInterface";

            //---------------------------------------------------------
            // TEMPORARY DATA. REAL DATA NEEDS TO BE OBTAINED FROM DB
            //---------------------------------------------------------
            Student *newStudent = new Student(15, "Joe Smith", "joesmith", 10101010);

            // Create dummy items and add them to the shopping cart
            SellableItem *t1 = new Textbook(1, "The First Book", 554563, 1, "123456678");
            SellableItem *c1 = new Chapter(5, NULL, 1, "Chapter One", 432, true);
            SellableItem *s1 = new Section(9, NULL, 1, "Section One", 325, true);

            newStudent->setCreditCardInfo(new CreditCardInfo("Test", "Test@sfddsf", "fake address", "12344556", "VISA", "12334343", "25/2/1", "123"));
            newStudent->setDeliveryInfo(new DeliveryInfo("Test@sfddsf"));

            studentIF = new CartManagementInterface(0, network, newStudent);
            newStudent->getCart()->addItem(t1);
            newStudent->getCart()->addItem(c1);
            newStudent->getCart()->addItem(s1);
            studentIF->show();
            loginWin->close();
            break;
          }

        case Role::ContentManagerUser:
            qDebug() << "LoginControl::loginSuccessful creating cmInterface";

            cmIF = new ContentManagementInterface(0, network);
            cmIF->show();
            loginWin->close(); // Assuming we aren't going to handle logouts..
            break;

        case Role::AdministratorUser:
            qDebug() << "TODO: handle admin login";
            break;
    }
}

void LoginControl::loginFailed(QUuid requestId) {
    qDebug() << "Login::failedLogin for: " << requestId;
}
