#ifndef BILLINGWINDOW_H
#define BILLINGWINDOW_H

#include <QDialog>
#include "CartRequestsAPI.h"
#include "Entity/Student.h"
#include "Entity/CreditCardInfo.h"
#include "PlaceOrderControl.h"

namespace Ui {
    class BillingWindow;
}

class PlaceOrderControl;


class BillingWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit BillingWindow(QWidget *parent = 0, PlaceOrderControl *ctrl = NULL);
        ~BillingWindow();

    private slots:
        void on_cancelButton_clicked();
        void on_submitButton_clicked();

    private:
        Ui::BillingWindow *ui;

        PlaceOrderControl *placeOrderCtrl;

};

#endif // BILLINGWINDOW_H
