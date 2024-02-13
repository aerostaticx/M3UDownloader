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
    void createHashes(const QJsonObject& artistsObj,const QJsonObject& albumObj,const QJsonObject& tracksObj);

    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QString userToken = "";
    QString userId = "";
    std::unordered_map<QString,QString> artistHash; //<artistID,artistName>
    std::unordered_map<QString,QString> albumHash; //<albumID,albumName>
    std::unordered_map<QString,std::array<QString,3>> songHash; //<songID : array<songName, albumName, artistName>>
    std::unordered_map<QString,std::vector<QString>> playlistToSongHash; //<playlistID : vector<songID>>
    std::unordered_map<QString,QString> playlistHash; //<playlistName : playlistID>

signals:
    void emitReplyError(replyErrors outputError);
};

#endif // NETWORKHANDLER_H
