#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new QNetworkAccessManager())
{
    ui->setupUi(this);
    // QNetworkProxy proxy;
    // proxy.setType(QNetworkProxy::NoProxy);
    // manager->setProxy(proxy);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::on_loginButton_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://api.ibroadcast.com"));
    request.setHeader(QNetworkRequest::UserAgentHeader,QVariant("M3UDownloader/1.0 (Windows11; en-US; x64)"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));

    QJsonObject jsonObject
    {
        {"client","Will"},
        {"app_id",1134},
        {"version","1.0"},
        {"device_name","WillComp"},
        {"user_agent",request.header(QNetworkRequest::UserAgentHeader).toString()},
        {"mode","login_token"},
        {"type","account"},
        {"login_token",ui -> tokenInput -> text()}
    };

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonPayload = jsonDoc.toJson();
    QNetworkReply* reply = this -> manager -> post(request,jsonPayload);
    QObject::connect(reply,&QNetworkReply::finished,[=](){
        if(reply -> error() == QNetworkReply::NoError)
        {
            qInfo() << reply -> readAll();
        }
        else
        {
            qInfo() << reply -> errorString();
        }
    });
}

