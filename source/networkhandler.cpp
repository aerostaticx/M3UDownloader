#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject{parent}, manager{new QNetworkAccessManager}
{}

NetworkHandler::~NetworkHandler()
{
    delete manager;
}

void NetworkHandler::getLibraryReplyHandler()
{
    if(this -> reply -> error() == QNetworkReply::NoError)
    {
        QJsonDocument json = QJsonDocument::fromJson(reply -> readAll());
        if(json["result"] == false)
        {
            emit this -> emitReplyError(replyErrors::LOGIN_ERROR);
            return;
        }
        else
        {
            QJsonObject masterObj = json.object();
            QJsonObject libraryObj = json["library"].toObject();

            emit this -> emitPopulateLibrary(libraryObj);
            emit this -> emitLoginSuccessful();
        }
    }
    else
    {
        emit this -> emitReplyError(replyErrors::LOGIN_ERROR);
        return;
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
            return;
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
        return;
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
