#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkProxy>
#include <QHostInfo>
#include "version.h"

enum replyErrors
{
    LOGIN_ERROR = 0,
    TOKEN_ERROR,
};

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);
    ~NetworkHandler();
public slots:
    void login(QString loginToken);

private slots:
    void loginReplyHandler();
    void getLibraryReplyHandler();
private:
    void getLibrary();
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QString userToken = "";
    QString userId = "";
    QJsonDocument library;

signals:
    void emitReplyError(replyErrors outputError);
};

#endif // NETWORKHANDLER_H
