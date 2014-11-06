#include "TPSGetRequiredBooksTask.h"
#include "TPSNetUtils.h"

#include <QDebug>

TPSGetRequiredBooksTask::TPSGetRequiredBooksTask(Server* srv)
    : TPSWorkerTask(srv)
{
}

void TPSGetRequiredBooksTask::run()
{
    qDebug() << "GetRequiredBooks task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    QString username;
    bool error = false;

    QDataStream in(iblock, QIODevice::ReadOnly);
    in >> username;

    QVector<int>* ids = new QVector<int>();

    qDebug() << "calling the getRequiredTextbooks API for user " << username;

    ServerResponse getBooks = server->getRequiredTextbooks(sessionId, username, ids);

    QVector<Textbook*>* textbooks = new QVector<Textbook*>(ids->size());

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    qDebug() << "writing " << ids->size() << " books to outgoing buffer...";

    for (int i = 0; i < ids->size(); ++i)
    {
        qint32 bookId = ((qint32) ids->at(i));
        Textbook *book;
        ServerResponse r = server->getTextbookDetails(sessionId, bookId, &book);

        if (r.code == Fail)
        {
            qDebug() << "Error: a failure has occurred while fetching textbook details for id"
                     << bookId;
            error = true;
            continue;
        } else {
            qDebug() << "Received book details: " << book->getName();
        }

        textbooks->replace(i, book);
    }

    // Write number of textbooks first

    QDataStream dataOut(&data,QIODevice::WriteOnly);

    dataOut << textbooks->size();

    // Write every textbook one by one

    for (Textbook* t_p : *textbooks)
    {
        TPSNetUtils::SerializeTextbook(&dataOut, t_p);
        delete t_p;
    }

    qDebug() << "formulating server response... ";

    setupResponse(response,
                  error ? 0x0 : 0x1,
                  &data,
                  &out);

    qDebug() << "Result of getRequiredBooks: " << error << "\n";

    emit result(response.responseCode, oblock);
}

