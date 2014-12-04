// Class: ViewCartOption
// Type: Boundary
// Description:
//     this class provides student users with the option to view/manage their cart
//
// Traceability: ViewCartOption class in the StudentInterface subsystem

#ifndef VIEWCARTOPTION_H
#define VIEWCARTOPTION_H

#include <QWidget>

#include "ViewCartControl.h"
#include "ClientNetworkHandler.h"
#include "Entity/Student.h"

namespace Ui {
    class ViewCartOption;
}

class ViewCartOption : public QWidget {
    Q_OBJECT

    public:
        explicit ViewCartOption(QWidget *parent = 0, ClientNetworkHandler *net = NULL);
        ~ViewCartOption();

    void setStudent(Student*);

    signals:
        void hideStudentMainMenuWindow();

    private slots:
        void on_viewCartButton_clicked();

    private:
        Ui::ViewCartOption *ui;
        ClientNetworkHandler *network;

        Student *student;
};

#endif // VIEWCARTOPTION_H
