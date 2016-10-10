#include "usermenu.h"

#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserMenu* um = new UserMenu();
    um->show();

    return a.exec();
}


