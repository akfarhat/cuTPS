#include "CancelOrderControl.h"

CancelOrderControl::CancelOrderControl() {
}

CancelOrderControl::~CancelOrderControl() {

}

void CancelOrderControl::clearCart(Student *student) {
    student->getCart()->clearCart();
}
