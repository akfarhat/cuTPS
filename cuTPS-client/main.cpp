#include "ClientNetworkHandler.h"
#include "LoginControl.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create the only instance of the network handler
    ClientNetworkHandler network;

    LoginControl loginCtrl(&network);

    loginCtrl.startSession();

    return a.exec();
}
