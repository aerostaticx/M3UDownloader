#include "mainwindow.h"
#include "networkhandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkHandler nh;
    MainWindow w;
    w.show();

    //Async code
    QObject::connect(&w,&MainWindow::loginRequest,&nh,&NetworkHandler::login);
    QObject::connect(&nh,&NetworkHandler::emitReplyError,&w,&MainWindow::handleReplyErrors);

    return a.exec();
}
