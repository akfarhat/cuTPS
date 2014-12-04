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

namespace Ui {
    class ViewCartOption;
}

class ViewCartOption : public QWidget {
    Q_OBJECT

    public:
        ViewCartOption(QWidget *parent, ClientNetworkHandler *net);
        ~ViewCartOption();

    signals:
        void hideStudentMainMenuWindow();

    private slots:
        void on_viewCartButton_clicked();

    private:
        Ui::ViewCartOption *ui;
        ClientNetworkHandler *network;

        User *student;
};

#endif // VIEWCARTOPTION_H
