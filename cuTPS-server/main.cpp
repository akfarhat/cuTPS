#include <QCoreApplication>
#include "TPSServerAsync.h"

#define MAX_THREADS 15  // TODO: move that away

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QThreadPool::globalInstance()->setMaxThreadCount(MAX_THREADS);
    // Create + Start the server.
    TPSServerAsync server;
    server.StartServer();

    return a.exec();
}
