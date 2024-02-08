#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
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
    void handleReplyErrors(replyErrors inputError);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getTokenInput();

private slots:
    void showLoginError();
    void hideLoginError();
    void on_loginButton_clicked();
private:
    Ui::MainWindow *ui;

signals:
    void loginRequest(QString loginToken);

};
#endif // MAINWINDOW_H
