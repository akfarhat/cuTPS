#include "Tests.h"
#include "ui_Tests.h"

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

    // Define some values that must be in the database
    // for test cases/diagnostics requests
    userCreds.username = "joesmith";
    userCreds.password = "alamepassword";

    sessCreds.username = "joesmith";
    sessCreds.sessionID = 0;
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
}

void Tests::setResult(ServerResponse *s) {

    QString resMsg;

    QTextStream(&resMsg) << "response code: " << s->code
                         << ", \nsessionID: " << s->sessionID
                         << "\nMessage: " << s->message;

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
    updateResults("Logging in as Joe:");

    ServerResponse res;

    network.login(&userCreds, &res);

    setResult(&res);
}

void Tests::on_viewReqTextsButton_clicked() {
    clearResults();
    updateResults("View required textbooks:");

    ServerResponse res;

    ViewRequiredBooksControl *ViewRequiredBooksCtrl = new ViewRequiredBooksControl();

    ViewRequiredBooksCtrl->getRequiredBooks(&sessCreds, &res);

    delete ViewRequiredBooksCtrl;

    setResult(&res);
}

void Tests::on_viewBookDetailsButton_clicked() {
    clearResults();
    updateResults("View book details:");

    Textbook *aBook;

    ServerResponse res;

    ViewBookDetailsControl *viewBookDetailsCtrl = new ViewBookDetailsControl();

    viewBookDetailsCtrl->getBookDetails(&sessCreds, aBook, &res);

    delete viewBookDetailsCtrl;

    setResult(&res);
}

void Tests::on_submitOrderButton_clicked() {
    clearResults();
    updateResults("Submit order:");

    Textbook *book;

    Chapter c1(book, 1, "someItem", 1.54f);
    Chapter c2(book, 2, "anotherItem", 99.42f);
    QVector<SellableItem*> items;

    items.append(&c1);
    items.append(&c2);

    CreditCardInfo creditInfo("Joe Smith", "smith@gmail.com", "43 streetName",
                              "613-555-1234", "Mastercard", "1305123234234",
                              "12/12/12", "123");

    DeliveryInfo deliveryInfo("smith@gmail.com");

    Order order(&items, &creditInfo, &deliveryInfo);

    ServerResponse res;

    SubmitOrderControl *submitOrderCtrl = new SubmitOrderControl();

    submitOrderCtrl->submitOrder(&sessCreds, &order, &res);

    delete submitOrderCtrl;

    setResult(&res);
}

void Tests::on_addCourseButton_clicked() {
    clearResults();
    updateResults("Add course:");

    Course c("COMP3004");

    ServerResponse res;

    AddCourseControl *addCourseCtrl = new AddCourseControl();

    addCourseCtrl->addCourse(&sessCreds, &c, &res);

    delete addCourseCtrl;

    setResult(&res);
}

void Tests::on_addBookButton_clicked() {
    clearResults();
    updateResults("Add book:");

    Textbook *textbook;

    ServerResponse res;

    AddBookControl *addBookCtrl = new AddBookControl();

    addBookCtrl->addBook(&sessCreds, textbook, &res);

    setResult(&res);
}
