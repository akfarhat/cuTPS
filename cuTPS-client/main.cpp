#include "ClientNetworkHandler.h"
#include "LoginControl.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create the only instance of the network handler
    ClientNetworkHandler network;

    // Connect the network handler to the server
    // TODO: get the server connection details from a config (we don't store any pers. data on client)
    // TODO: move this away frome here and connect on login button click
    QHostAddress localhost(QHostAddress::LocalHost);
    QHostAddress remoteSrv("192.241.250.122"); // this server should be always up for testing purposes
    network.connectToServer(localhost, 12754);

    LoginControl loginCtrl(&network);

    loginCtrl.startSession();

    return a.exec();
}
