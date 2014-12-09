#include "ContentRequestAPI.h"

#include <QDebug>

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

QUuid ContentRequestAPI::modifyBook(Textbook &book)
{
    qDebug() << "networking: " << networking;
    return this->networking->addBook(book);
}

QUuid ContentRequestAPI::modifyChapter(int textId, Chapter &chapter)
{
    return this->networking->addChapter(textId, chapter);
}

QUuid ContentRequestAPI::modifySection(int textId, int chapId, Section &section)
{
    return this->networking->addSection(textId, chapId, section);
}

QUuid ContentRequestAPI::deleteTextbook(int itemId)
{
    return this->networking->removeBook(itemId);
}

QUuid ContentRequestAPI::deleteChapter(int itemId)
{
    return this->networking->removeChapter(itemId);
}


QUuid ContentRequestAPI::deleteSection(int itemId)
{
    return this->networking->removeSection(itemId);
}


QUuid ContentRequestAPI::getAllBooks()
{
    return this->networking->getAllBooks();
}
