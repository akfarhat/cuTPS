#include <QCoreApplication>
#include <ServerNetworking/ServerAsync.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Create + Start the server.
    ServerAsync server;
    server.StartServer();

    return a.exec();
}
