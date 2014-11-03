#include "AddBookControl.h"

AddBookControl::AddBookControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI) {}

AddBookControl::~AddBookControl() {

}

void AddBookControl::addBook(QUuid &reqId, Textbook &newTextbook) {
    reqId = network.addBook(newTextbook);
}
