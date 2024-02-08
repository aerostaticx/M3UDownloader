#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject{parent}, manager{new QNetworkAccessManager}
{}

NetworkHandler::~NetworkHandler()
{
    delete manager;
}

void NetworkHandler::replyHandler()
{
    if(this -> reply -> error() == QNetworkReply::NoError)
    {
        QJsonDocument json = QJsonDocument::fromJson(reply -> readAll());
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

    QObject::connect(this -> reply,&QNetworkReply::finished,this,&NetworkHandler::replyHandler);
}
