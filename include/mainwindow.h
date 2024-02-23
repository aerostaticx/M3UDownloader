#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include "networkhandler.h"

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
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getTokenInput();

private slots:
    void showLoginError(const QString error);
    void hideLoginError();
    void on_loginButton_clicked();
    void on_convertButton_clicked();
    void on_logoutButton_clicked();

    void on_chooseDirectoryButton_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void conversionRequest();
    void loginRequest(QString loginToken);

};
#endif // MAINWINDOW_H
