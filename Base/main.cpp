#include "view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View * w = new View();
    w->show();

    return a.exec();
}
