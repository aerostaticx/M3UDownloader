#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include "networkhandler.h"
#include "conversionHandler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void transitionConvertWindow();
    void transitionMainWindow();
    void handleReplyErrors(replyErrors inputError);
    void handleConversionErrors(conversionErrors conversionError);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getTokenInput();

private slots:
    void on_loginButton_clicked();
    void on_convertButton_clicked();
    void on_logoutButton_clicked();

    void on_chooseDirectoryButton_clicked();

private:
    void showConversionError(const QString error);
    void hideConversionError();
    void showLoginError(const QString error);
    void hideLoginError();
    Ui::MainWindow *ui;

signals:
    void conversionRequest(QString playlistRequested, QString saveLocation, QString relativeStructure);
    void loginRequest(QString loginToken);

};
#endif // MAINWINDOW_H
