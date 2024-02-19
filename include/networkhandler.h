#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkProxy>
#include <QHostInfo>
#include <QTextCodec>
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
    void createHashes(const QJsonObject& libraryObj);

    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QString userToken = "";
    QString userId = "";
signals:
    void emitReplyError(replyErrors outputError);
    void emitPopulateLibrary(QJsonObject libraryObj);
    void emitLoginSuccessful();
};

#endif // NETWORKHANDLER_H
