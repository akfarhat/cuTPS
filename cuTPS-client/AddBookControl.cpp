#include "AddBookControl.h"

AddBookControl::AddBookControl(ContentRequestAPI *serverAPI)
    : network(serverAPI) {}

AddBookControl::~AddBookControl() {

}

void AddBookControl::addBook(QUuid &reqId, Textbook &newTextbook) {
    reqId = network->addBook(newTextbook);
}

void AddBookControl::addChapter(QUuid &reqId, int textId, Chapter &newChapter) {
    reqId = network->addChapter(textId, newChapter);
}

void AddBookControl::addSection(QUuid &reqId, int textId, int chapId, Section &newSection) {
    reqId = network->addSection(textId, chapId, newSection);
}
