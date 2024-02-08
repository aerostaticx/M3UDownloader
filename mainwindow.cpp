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

void MainWindow::handleReplyErrors(replyErrors inputError)
{
    switch (inputError) {
    case replyErrors::LOGIN_ERROR:
        this -> showLoginError();
        break;
    default:
        break;
    }
}

QString MainWindow::getTokenInput()
{
    return this -> ui -> tokenInput -> text();
}

void MainWindow::showLoginError()
{
    this -> ui -> loginFailureLabel -> setHidden(false);
}

void MainWindow::hideLoginError()
{
    this -> ui -> loginFailureLabel -> setHidden(true);
}

void MainWindow::on_loginButton_clicked()
{
    this -> hideLoginError();
    emit loginRequest(this -> getTokenInput());
}

