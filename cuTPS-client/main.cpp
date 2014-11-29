#include "ClientNetworkHandler.h"
#include "LoginControl.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create the only instance of the network handler
    ClientNetworkHandler network;

    // Connect the network handler to the server
    // TODO: get the server connection details from a config
    QHostAddress addr(QHostAddress::LocalHost);
    network.connectToServer(addr, TPSConstants::PORT);

    LoginControl loginCtrl(&network);

    loginCtrl.startSession();

    return a.exec();
}
