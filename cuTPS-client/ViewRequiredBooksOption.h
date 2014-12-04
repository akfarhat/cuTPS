// Class: ViewRequiredBooksOption
// Type: Boundary
// Description:
//     this class provides student users with the option to
//     view the books associated with the courses which they are enrolled in
//
// Traceability: ViewRequiredBooksOption class in the StudentInterface subsystem

#ifndef VIEWREQUIREDBOOKSOPTION_H
#define VIEWREQUIREDBOOKSOPTION_H

#include <QWidget>
#include "ClientNetworkHandler.h"
#include "Entity/Student.h"

namespace Ui {
    class ViewRequiredBooksOption;
}

class ViewRequiredBooksOption : public QWidget {
    Q_OBJECT

    public:
        explicit ViewRequiredBooksOption(QWidget *parent = 0, ClientNetworkHandler *net = NULL, Student *stu = NULL);
        ~ViewRequiredBooksOption();

    private slots:
        void on_viewBooksButton_clicked();

    private:
        Ui::ViewRequiredBooksOption *ui;
        ClientNetworkHandler *network;

        Student *student;
};

#endif // VIEWREQUIREDBOOKSOPTION_H
