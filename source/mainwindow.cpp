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
        this -> showLoginError("There was a problem communicating with the iBroadcast API server. Please try logging in again.");
        break;
    case replyErrors::TOKEN_ERROR:
        this -> showLoginError("Your token was not found. Please make sure to enter the correct token.");
        break;
    default:
        break;
    }
}

void MainWindow::handleConversionErrors(conversionErrors inputError)
{
    switch (inputError) {
    case conversionErrors::PLAYLIST_NOT_FOUND_ERROR:
        this -> showConversionError("Playlist not found or empty.");
        break;
    default:
        break;
    }
}

QString MainWindow::getTokenInput()
{
    return this -> ui -> tokenInput -> text();
}

void MainWindow::showConversionError(const QString error)
{
    this -> ui -> conversionFailureLabel -> setHidden(false);
    this -> ui -> conversionFailureLabel -> setText("<font color='red'>" + error + "</font>");
}

void MainWindow::hideConversionError()
{
    this -> ui -> conversionFailureLabel -> setHidden(true);
}

void MainWindow::showLoginError(const QString error)
{
    this -> ui -> loginFailureLabel -> setHidden(false);
    this -> ui -> loginFailureLabel -> setText("<font color='red'>" + error + "</font>");
}

void MainWindow::hideLoginError()
{
    this -> ui -> loginFailureLabel -> setHidden(true);
}

void MainWindow::transitionConvertWindow()
{
    this -> ui -> stackedWidget -> setCurrentIndex(1);
}

void MainWindow::transitionMainWindow()
{
    this -> ui -> stackedWidget -> setCurrentIndex(0);
}

void MainWindow::on_loginButton_clicked()
{
    this -> hideLoginError();
    emit loginRequest(this -> getTokenInput());
}

void MainWindow::on_convertButton_clicked()
{
    //send the location input, the playlist name, and directory format to the conversionHandler
    //ConversionHandler also needs the library hashes.
    emit conversionRequest(this -> ui -> playlistInput -> text(), this -> ui -> saveLocationInput -> text(), this -> ui -> saveStructureCombo -> currentText());
}

void MainWindow::on_logoutButton_clicked()
{
    transitionMainWindow();
}

void MainWindow::on_chooseDirectoryButton_clicked()
{
    QString inputDirectory = QFileDialog::getExistingDirectory(this,tr("Open Directory"),"",QFileDialog::ShowDirsOnly);
    this -> ui -> saveLocationInput -> setText(inputDirectory);
}


void MainWindow::on_playlistInput_textChanged(const QString &arg1)
{
    this -> ui -> conversionFailureLabel -> setHidden(true);
}

