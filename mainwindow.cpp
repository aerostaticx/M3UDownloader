#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->loginFailureLabel->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getTokenInput()
{
    return this -> ui -> tokenInput -> text();
}

void MainWindow::on_loginButton_clicked()
{
    this -> ui -> loginFailureLabel -> setHidden(true);
    emit loginRequest(this -> getTokenInput());
}

