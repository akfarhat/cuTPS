#include "Tests.h"
#include "ui_Tests.h"


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

    ui->studentRadio->setChecked(true);

    ui->testCasesGroup->hide();

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
    connect(&network, SIGNAL(serverError(QUuid,int)), this, SLOT(serverErrorRecieved(QUuid, int)));

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
    this->ui->passFailInput->setText("");
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

    if (ui->studentRadio->isChecked()) {
        userCreds.username = "joesmith";
        userCreds.password = "alamepassword";
        sessCreds.username = "joesmith";
        userRole = Role::Student;
    } else if (ui->contentManagerRadio->isChecked()) {
        userCreds.username = "cm";
        userCreds.password = "pass";
        sessCreds.username = "joesmith";
        userRole = Role::ContentManager;
    }

    sessCreds.sessionID = 0;

    loginCtrl = new LoginControl(network);

    QUuid requestId;

    loginCtrl->login(requestId, userCreds);


    delete loginCtrl;

}

void Tests::on_viewReqTextsButton_clicked() {
    clearResults();
    updateResults("View required textbooks:");

    viewReqBooksCtrl = new ViewRequiredBooksControl(network);

    QUuid requestId;

    viewReqBooksCtrl->getRequiredBooks(requestId, sessCreds.username);

    delete viewReqBooksCtrl;

}

void Tests::on_viewBookDetailsButton_clicked() {
    clearResults();
    updateResults("View book details:");

    Textbook aBook(1, "Comp 3004 - The Book", 9949, true, "123-456-7890");

    viewBookDetailsCtrl = new ViewBookDetailsControl(network);

    QUuid requestId;

    viewBookDetailsCtrl->getBookDetails(requestId, aBook);

    delete viewBookDetailsCtrl;

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


    submitOrderCtrl = new SubmitOrderControl(network);

    QUuid requestId;

    submitOrderCtrl->submitOrder(requestId, order);

    delete submitOrderCtrl;

}

void Tests::on_addCourseButton_clicked() {
    clearResults();
    updateResults("Add course:");

    // Create some hard coded objects to test the request
    QVector<Textbook*> books;
    books.append(new Textbook(2, "Comp 3004 Textbook 2", 5153, true, "123-456-710"));
    books.append(new Textbook(3, "Comp 3004 Textbook 3", 9153, true, "123-456-711"));

    Course *c = new Course("COMP 3004", "Advanced Diagrams", books);

    addCourseCtrl = new AddCourseControl(network);

    QUuid requestId;

    addCourseCtrl->addCourse(requestId, *c);

    delete addCourseCtrl;

}

void Tests::on_addBookButton_clicked() {
    clearResults();
    updateResults("Add book:");

    Textbook textbook("Introduction to Calculus", 120);


    addBookCtrl = new AddBookControl(network);

    QUuid requestId;

    addBookCtrl->addBook(requestId, textbook);

    delete addBookCtrl;

}

void Tests::loginSuccessful(QUuid requestId) {
        clearResults();

        updateResults("Logged in as user " + userCreds.username);
        setPassed();

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


}

void Tests::orderStatusReceived(QUuid requestId, int code) {
    clearResults();
    setPassed();
    updateResults("Order request recieved by server");
}

void Tests::updateCompleted(QUuid requestId, int code) {
    clearResults();
    if (code == 0) {
        setFailed();
        updateResults("Failed to add the course for request: "
                      + requestId);
    } else if (code == 1) {
        setPassed();
        updateResults("Succesfully added course for request: "
                      + requestId);
    }
}

void Tests::textbookDetailsReceived(QUuid requestId, int code, Textbook* resBook) {
    clearResults();
    setPassed();
    updateResults(resBook->getDetails());
}

void Tests::textbookLookupCompleted(QUuid requestId, int code, QVector<Textbook*>* resBooks) {
    clearResults();
    setPassed();

    int i = 0;
    // TODO: Test this
    for (i = 0; i < resBooks->size(); i++) {
        updateResults(resBooks->at(i)->getDetails() + "\n\n");
    }
}

void Tests::serverErrorRecieved(QUuid requestId, int error) {
    clearResults();
    setFailed();
    updateResults("Receieved error code " + QString::number(error) + " from server");
}
