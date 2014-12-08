// Class: CancelOrderControl
// Type: Control
// Description:
//     this class is responsible for handling the cancellation of an order by a student
//
// Traceability: CancelOrderControl class in the CartManagement subsystem

#ifndef CANCELORDERCONTROL_H
#define CANCELORDERCONTROL_H

#include "Entity/Student.h"

class CancelOrderControl {
    public:
        CancelOrderControl();
        ~CancelOrderControl();

        void clearCart(Student *);
};

#endif // CANCELORDERCONTROL_H
