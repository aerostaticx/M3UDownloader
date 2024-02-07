#include "mainwindow.h"
#include "networkhandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkHandler nh;
    MainWindow w;
    w.show();


    QObject::connect(&w,&MainWindow::loginRequest,&nh,&NetworkHandler::login);

    return a.exec();
}
