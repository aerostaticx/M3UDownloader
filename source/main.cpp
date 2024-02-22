#include "mainwindow.h"
#include "networkhandler.h"
#include "library.h"
#include "conversionHandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkHandler nh;
    Library l;
    MainWindow w;
    w.show();

    //Async code
    QObject::connect(&w,&MainWindow::loginRequest,&nh,&NetworkHandler::login);
    QObject::connect(&nh,&NetworkHandler::emitReplyError,&w,&MainWindow::handleReplyErrors);
    QObject::connect(&nh,&NetworkHandler::emitPopulateLibrary,&l,&Library::populateLibrary);
    QObject::connect(&nh,&NetworkHandler::emitLoginSuccessful,&w,&MainWindow::transitionConvertWindow);

    return a.exec();
}
