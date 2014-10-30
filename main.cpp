#include "Client/LoginWindow.h"
#include "Client/Tests.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Tests testWindow;
    testWindow.show();

    // LoginWindow w;
    //w.show();

    return a.exec();
}
