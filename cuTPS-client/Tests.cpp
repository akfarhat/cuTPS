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

#include <QDebug>

Tests::Tests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tests)
{
    ui->setupUi(this);

    this->setWindowTitle("Test Cases");

    // Define some values that must be in the database
    // for test cases/diagnostics requests
    userCreds.username = "joesmith";
    userCreds.password = "alamepassword";

    sessCreds.username = "joesmith";
    sessCreds.sessionID = 0;

    // Connect the network handler to the server
    // TODO: get the server connection details from a config
    QHostAddress addr(QHostAddress::LocalHost);
    network.connectToServer(addr, TPSConstants::PORT);

    // Bind a handler to server responses to our requests
    connect(&network, SIGNAL(loginSuccessful(QUuid)), this, SLOT(loginSuccessful(QUuid)));
    connect(&network, SIGNAL(orderStatusReceived(QUuid, int)), this, SLOT(orderStatusReceived(QUuid, int)));
    connect(&network, SIGNAL(updateCompleted(QUuid, int)), this, SLOT(updateCompleted(QUuid, int)));
    connect(&network, SIGNAL(textbookDetailsReceived(QUuid, int, Textbook*)), this, SLOT(textbookDetailsReceived(QUuid, int, Textbook*)));
    connect(&network, SIGNAL(textbookLookupCompleted(QUuid, int, QVector<Textbook*>*)), this, SLOT(textbookLookupCompleted(QUuid, int, QVector<Textbook*>*)));

}

Tests::~Tests() {
    delete ui;
}

void Tests::updateResults(QString msg) {
    QString currRes = this->ui->resultInput->toPlainText();
    this->ui->resultInput->setText(currRes.append(QString(msg + "\n")));
}

void Tests::clearResults() {
    this->ui->resultInput->setText("");
    this->ui->passFailInput->setText("");
}

void Tests::setResult(ServerResponse *s) {

    QString resMsg;

    QTextStream(&resMsg) << "response code: " << s->code << ", \nsessionID: " << (s->sessionID).toString() << "\nMessage: " << s->message;

    updateResults(resMsg);

    if (s->code == Success) {
        this->ui->passFailInput->setText("Passed");
    } else {
        this->ui->passFailInput->setText("Failed");
    }
}

void Tests::setPassed() {
    this->ui->passFailInput->setText("Passed");
}

void Tests:: setFailed() {
    this->ui->passFailInput->setText("Failed");
}

// Handle the test case button click events
// create the relevant objects and send them
// to the network interface methods

void Tests::on_loginButton_clicked() {
    clearResults();
    updateResults("Logging in as Joe:");

    LoginControl *loginCtrl = new LoginControl(network);

    loginCtrl->login(userCreds);

    delete loginCtrl;
}

void Tests::on_viewReqTextsButton_clicked() {
    clearResults();
    updateResults("View required textbooks:");

    //ServerResponse res;

    ViewRequiredBooksControl *ViewRequiredBooksCtrl = new ViewRequiredBooksControl(network);

    QUuid requestId;

    ViewRequiredBooksCtrl->getRequiredBooks(requestId, sessCreds.username);

    delete ViewRequiredBooksCtrl;

    //setResult(&res);
}

void Tests::on_viewBookDetailsButton_clicked() {
    clearResults();
    updateResults("View book details:");

    Textbook aBook(1, "Comp 3004 - The Book", 9949, true, "123-456-7890");

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

void Tests::loginSuccessful(QUuid requestId) {
    updateResults("Successful login for request: " + requestId);
    setPassed();
}

void Tests::orderStatusReceived(QUuid requestId, int code) {
    // TODO: update the results in the UI with these params
}

void Tests::updateCompleted(QUuid requestId, int code) {
    // TODO: update the results in the UI with these params
}

void Tests::textbookDetailsReceived(QUuid requestId, int code, Textbook* resBook) {
    // TODO: update the results in the UI with these params
}

void Tests::textbookLookupCompleted(QUuid requestId, int code, QVector<Textbook*>* resBooks) {
    // TODO: update the results in the UI with these params
}
