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
        void on_loginButton_clicked();

        void on_viewReqTextsButton_clicked();

        void on_viewBookDetailsButton_clicked();

        void on_submitOrderButton_clicked();

        void on_addCourseButton_clicked();

        void on_addBookButton_clicked();

    private:
        Ui::Tests *ui;

        ClientNetworkHandler network;

        UserCredentials userCreds;

        SessionCredentials sessCreds;

        void updateResults(QString);

        void clearResults();

        void setResult(ServerResponse *);
};

#endif // TESTS_H
