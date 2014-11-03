#include "Tests.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tests testWindow;
    testWindow.show();

    return a.exec();
}
