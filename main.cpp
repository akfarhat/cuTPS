#include "Client/LoginWindow.h"
#include <QApplication>

#include <Entity/Course.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;

    w.show();

    return a.exec();
}
