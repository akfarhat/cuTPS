#include "AddBookControl.h"

AddBookControl::AddBookControl() {

}

AddBookControl::~AddBookControl() {

}

void AddBookControl::addBook(QUuid &reqId, Textbook &newTextbook) {
    reqId = network.addBook(newTextbook);
}
