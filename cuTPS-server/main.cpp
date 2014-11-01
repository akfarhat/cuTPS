#include <QCoreApplication>
#include "TPSServerAsync.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create + Start the server.
    TPSServerAsync server;
    server.StartServer();

    return a.exec();
}
