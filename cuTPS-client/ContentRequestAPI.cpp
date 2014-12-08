#include "ContentRequestAPI.h"

ContentRequestAPI::ContentRequestAPI(QObject *parent, ClientNetworkHandler *net) :
    QObject(parent)
{
    this->networking = net;
}

QUuid ContentRequestAPI::addBook(Textbook& text)
{
    return this->networking->addBook(text);
}

QUuid ContentRequestAPI::addChapter(int bookId, Chapter& chapter)
{
    return this->networking->addChapter(bookId, chapter);
}

QUuid ContentRequestAPI::addSection(int bookId, int chapId, Section& section)
{
    return this->networking->addSection(bookId, chapId, section);
}

QUuid ContentRequestAPI::deleteItem(int itemId)
{
    // TODO: return the result of the actual networking request

    QUuid id;
    return id;
}
