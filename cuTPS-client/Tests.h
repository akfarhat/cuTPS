// Class: Tests
// Type: User Interface / Control
// Description:
//     This class provides the implementation for test cases
//     invoked by the user. Test cases will use pre-defined
//     values, and make the requests to the server via
//     the ClientNetworkHandler

#ifndef TESTS_H
#define TESTS_H

#include <QDialog>
#include <QString>
#include "ClientNetworkHandler.h"
#include "Utils.h"

namespace Ui {
    class Tests;
}

class Tests : public QDialog
{
    Q_OBJECT

    public:
        explicit Tests(QWidget *parent = 0);
        ~Tests();

    private slots:
        // Handlers for button presses, each method represents
        // a different API request
        void on_loginButton_clicked();

        void on_viewReqTextsButton_clicked();

        void on_viewBookDetailsButton_clicked();

        void on_submitOrderButton_clicked();

        void on_addCourseButton_clicked();

        void on_addBookButton_clicked();

    private:
        // The UI window element
        Ui::Tests *ui;

        // Network handler to connect to the server
        ClientNetworkHandler network;

        UserCredentials userCreds;

        SessionCredentials sessCreds;

        // Append a status string to the results box
        void updateResults(QString);

        // Clear the status / results box
        void clearResults();

        // Set the results from the server in the status box
        void setResult(ServerResponse *);
};

#endif // TESTS_H
