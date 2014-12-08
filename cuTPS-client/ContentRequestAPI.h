// Class: ContentRequestAPI
// Description:
//   Used to interface all of the ContentManagement subsyste
//   requests to the ClientNetwokring subsystem, reducing coupling.
// Traceability:
//   The ContentRequestAPI class in the ContentManagement subsystem

#ifndef CONTENTREQUESTAPI_H
#define CONTENTREQUESTAPI_H

#include <QObject>

#include "ClientNetworkHandler.h"

class ContentRequestAPI : public QObject
{
    Q_OBJECT

    public:
        explicit ContentRequestAPI(QObject *parent = 0, ClientNetworkHandler *net = NULL);
        QUuid addBook(Textbook&);
        QUuid addChapter(int, Chapter&);
        QUuid addSection(int, int, Section&);
        QUuid modifyBook(Textbook&);
        QUuid modifyChapter(int, Chapter&);
        QUuid modifySection(int, int, Section&);
        QUuid deleteTextbook(int);
        QUuid deleteChapter(int);
        QUuid deleteSection(int);
        QUuid getAllBooks();

    signals:

    public slots:

    private:
        ClientNetworkHandler *networking;

};

#endif // CONTENTREQUESTAPI_H
