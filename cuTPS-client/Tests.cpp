#include "Tests.h"
#include "ui_Tests.h"

#include "LoginControl.h"
#include "ViewRequiredBooksControl.h"
#include "ViewBookDetailsControl.h"
#include "SubmitOrderControl.h"
#include "AddCourseControl.h"
#include "AddBookControl.h"

#include "Entity/SellableItem.h"
#include "Entity/Textbook.h"
#include "Entity/Chapter.h"
#include "Entity/CreditcardInfo.h"
#include "Entity/DeliveryInfo.h"

#include <QVector>
#include <QTextStream>

Tests::Tests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tests)
{
    ui->setupUi(this);

    this->setWindowTitle("Test Cases");

    ui->studentRadio->setChecked(true);

    ui->testCasesGroup->hide();

    // Define some values that must be in the database
    // for test cases/diagnostics requests

    //contentManagerCreds.username = "cm";
    //contentManagerCreds.password = "pass";

    sessCreds.username = "joesmith";
    sessCreds.sessionID = 0;

    // Connect the network handler to the server
    // TODO: get the server connection details from a config
    QHostAddress addr(QHostAddress::LocalHost);
    network.connectToServer(addr, TPSConstants::PORT);
}

Tests::~Tests() {
    network.disconnectFromServer();
    delete ui;
}

void Tests::updateResults(QString msg) {
    QString currRes = this->ui->resultInput->toPlainText();
    this->ui->resultInput->setText(currRes.append(QString(msg + "\n")));
}

void Tests::clearResults() {
    this->ui->resultInput->setText("");
}

void Tests::setResult(ServerResponse *s) {

    QString resMsg;

    QTextStream(&resMsg) << "response code: " << s->code << "\nMessage: " << s->message;

    updateResults(resMsg);

    if (s->code == Success) {
        this->ui->passFailInput->setText("Passed");
    } else {
        this->ui->passFailInput->setText("Failed");
    }
}

// Handle the test case button click events
// create the relevant objects and send them
// to the network interface methods

void Tests::on_loginButton_clicked() {
    clearResults();

    Role userRole;

    if (ui->studentRadio->isChecked()) {
        userCreds.username = "joesmith";
        userCreds.password = "alamepassword";
        userRole = Role::Student;
    } else if (ui->contentManagerRadio->isChecked()) {
        userCreds.username = "cm";
        userCreds.password = "pass";
        userRole = Role::ContentManager;
    }

    LoginControl *loginCtrl = new LoginControl(network);


    if (network.isConnected()) {
        ServerResponse response;

        // Send the login request and wait for the signal
        QEventLoop loop;

        this->connect(&network, SIGNAL(loginSuccessful(QUuid)), &loop, SLOT(quit()));
        this->connect(&network, SIGNAL(serverError(QUuid,int)), &loop, SLOT(quit()));

        updateResults("Logging in...");

        QUuid requestId = loginCtrl->login(userCreds);

        loop.exec();

        clearResults();

        if (network.isValid()) {
            response.code = ResponseCode::Success;
            response.message = "Logged in as user " + userCreds.username;
            setResult(&response);

            // Show the test cases
            ui->testCasesGroup->show();

            if (userRole == Role::Student) {
                // Show the student test cases and hide the content manager test cases from the student
                ui->viewReqTextsGroup->show();
                ui->viewTextDetailsGroup->show();
                ui->submitOrderGroup->show();
                ui->addBooksGroup->hide();
                ui->addCourseGroup->hide();
            } else if (userRole == Role::ContentManager) {
                // Show the content manager test cases and hide the student test cases from the content manager
                ui->addBooksGroup->show();
                ui->addCourseGroup->show();
                ui->viewTextDetailsGroup->show();
                ui->viewReqTextsGroup->hide();
                ui->submitOrderGroup->hide();
            }
        } else {
           response.code = ResponseCode::Fail;
           response.message = "Error: login failed";
           setResult(&response);
        }
    } else {
        updateResults("Error: not connected to server");
    }

    delete loginCtrl;

}

void Tests::on_viewReqTextsButton_clicked() {
    clearResults();
    updateResults("View required textbooks:");

    //ServerResponse res;

    ViewRequiredBooksControl *ViewRequiredBooksCtrl = new ViewRequiredBooksControl(network);

    QUuid requestId;

    ViewRequiredBooksCtrl->getRequiredBooks(requestId);

    delete ViewRequiredBooksCtrl;

    //setResult(&res);
}

void Tests::on_viewBookDetailsButton_clicked() {
    clearResults();
    updateResults("View book details:");

    Textbook aBook("Software Engineering", 199.99);

    //ServerResponse res;

    ViewBookDetailsControl *viewBookDetailsCtrl = new ViewBookDetailsControl(network);

    QUuid requestId;

    viewBookDetailsCtrl->getBookDetails(requestId, aBook);

    delete viewBookDetailsCtrl;

    //setResult(&res);
}

void Tests::on_submitOrderButton_clicked() {
    clearResults();
    updateResults("Submit order:");

    Textbook *book;

    Chapter c1(book, 1, "someItem", 1.54f);
    Chapter c2(book, 2, "anotherItem", 99.42f);
    QVector<qint32> items;

    items.append(c1.getId());
    items.append(c2.getId());

    CreditCardInfo creditInfo("Joe Smith", "smith@gmail.com", "43 streetName",
                              "613-555-1234", "Mastercard", "1305123234234",
                              "12/12/12", "123");

    DeliveryInfo deliveryInfo("smith@gmail.com");

    Order order(&items, &creditInfo, &deliveryInfo);

    //ServerResponse res;

    SubmitOrderControl *submitOrderCtrl = new SubmitOrderControl(network);

    QUuid requestId;

    submitOrderCtrl->submitOrder(requestId, order);

    delete submitOrderCtrl;

    //setResult(&res);
}

void Tests::on_addCourseButton_clicked() {
    clearResults();
    updateResults("Add course:");

    Course c("COMP3004");

    //ServerResponse res;

    AddCourseControl *addCourseCtrl = new AddCourseControl(network);

    QUuid requestId;

    addCourseCtrl->addCourse(requestId, c);

    delete addCourseCtrl;

    //setResult(&res);
}

void Tests::on_addBookButton_clicked() {
    clearResults();
    updateResults("Add book:");

    Textbook textbook("Introduction to Calculus", 120);

    //ServerResponse res;

    AddBookControl *addBookCtrl = new AddBookControl(network);

    QUuid requestId;

    addBookCtrl->addBook(requestId, textbook);

    //setResult(&res);
}
