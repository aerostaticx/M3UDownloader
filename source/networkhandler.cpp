#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject{parent}, manager{new QNetworkAccessManager}
{}

NetworkHandler::~NetworkHandler()
{
    delete manager;
}

void NetworkHandler::createHashes(const QJsonObject& artistsObj,const QJsonObject& albumsObj, const QJsonObject& tracksObj)
{
    QJsonObject artistMap = artistsObj["map"].toObject();
    for(auto it = artistsObj.begin(); it != artistsObj.end() - 1; ++it)
    {
        QString artistID = it.key();
        QJsonValue artistName = it.value();
        this -> artistHash[artistID] = artistName[artistMap["name"].toInt()].toString();
    }

    QJsonObject albumMap = albumsObj["map"].toObject();
    for(auto it = albumsObj.begin(); it != albumsObj.end() - 1; ++it)
    {
        QString albumID = it.key();
        QJsonValue albumName = it.value();
        this -> albumHash[albumID] = albumName[albumMap["name"].toInt()].toString();
    }

    QJsonObject trackMap = tracksObj["map"].toObject();
    for(auto it = tracksObj.begin(); it != tracksObj.end() - 1; ++it)
    {
        QString trackID = it.key();
        QJsonValue trackInfo = it.value();
        this -> songHash[trackID] = {trackInfo[trackMap["title"].toInt()].toString(),this -> albumHash[QString::number(trackInfo[trackMap["album_id"].toInt()].toInt())],this -> artistHash[QString::number(trackInfo[trackMap["artist_id"].toInt()].toInt())]};
    }
    qInfo() << "hi";


}

void NetworkHandler::getLibraryReplyHandler()
{
    if(this -> reply -> error() == QNetworkReply::NoError)
    {
        QJsonDocument json = QJsonDocument::fromJson(reply -> readAll());
        if(json["result"] == false)
        {
            emit this -> emitReplyError(replyErrors::LOGIN_ERROR);
        }
        else
        {
            QJsonObject masterObj = json.object();
            QJsonObject libraryObj = json["library"].toObject();
            QJsonObject artistsObj = libraryObj["artists"].toObject();
            QJsonObject albumsObj = libraryObj["albums"].toObject();
            QJsonObject tracksObj = libraryObj["tracks"].toObject();

            this -> createHashes(artistsObj,albumsObj,tracksObj);
        }
    }
    else
    {
        emit this -> emitReplyError(replyErrors::LOGIN_ERROR);
    }
}

void NetworkHandler::getLibrary()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://library.ibroadcast.com"));
    request.setHeader(QNetworkRequest::UserAgentHeader,QVariant("M3UDownloader/1.0 (Windows11; en-US; x64)"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));

    QJsonObject jsonObject
        {
            {"client","M3UDownloader"},
            {"version",VER_NUM},
            {"device_name",QHostInfo::localHostName()},
            {"token",this->userToken},
            {"user_id",this->userId},
            {"mode","library"}
        };

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonPayload = jsonDoc.toJson();
    this -> reply = this -> manager -> post(request,jsonPayload);

    QObject::connect(this -> reply,&QNetworkReply::finished,this,&NetworkHandler::getLibraryReplyHandler);
}

void NetworkHandler::loginReplyHandler()
{
    if(this -> reply -> error() == QNetworkReply::NoError)
    {
        QJsonDocument json = QJsonDocument::fromJson(reply -> readAll());
        if(json["result"] == false)
        {
            emit this -> emitReplyError(replyErrors::TOKEN_ERROR);
        }
        else
        {
            this -> userId = json["user"]["id"].toString();
            this -> userToken = json["user"]["token"].toString();
            this -> getLibrary();
        }
    }
    else
    {
        emit this -> emitReplyError(replyErrors::LOGIN_ERROR);
    }
}

void NetworkHandler::login(QString loginToken)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://api.ibroadcast.com"));
    request.setHeader(QNetworkRequest::UserAgentHeader,QVariant("M3UDownloader/1.0 (Windows11; en-US; x64)"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));

    QJsonObject jsonObject
        {
            {"client","M3UDownloader"},
            {"app_id",1113},
            {"version",VER_NUM},
            {"device_name",QHostInfo::localHostName()},
            {"user_agent",request.header(QNetworkRequest::UserAgentHeader).toString()},
            {"mode","login_token"},
            {"type","account"},
            {"login_token",loginToken}
        };

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonPayload = jsonDoc.toJson();
    this -> reply = this -> manager -> post(request,jsonPayload);

    QObject::connect(this -> reply,&QNetworkReply::finished,this,&NetworkHandler::loginReplyHandler);
}
