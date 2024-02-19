#include "library.h"

Library::Library(QObject *parent)
    : QObject{parent}
{}

Library::~Library()
{}

void Library::populateLibrary(const QJsonObject& libraryObj)
{
    QJsonObject artistsObj = libraryObj["artists"].toObject();
    QJsonObject albumsObj = libraryObj["albums"].toObject();
    QJsonObject tracksObj = libraryObj["tracks"].toObject();
    QJsonObject playlistsObj = libraryObj["playlists"].toObject();

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

    QJsonObject playlistMap = playlistsObj["map"].toObject();
    for(auto it = playlistsObj.begin(); it != playlistsObj.end() - 1; ++it)
    {
        QString playlistID = it.key();
        QJsonValue playlistInfo = it.value();
        QJsonArray trackIDs = playlistInfo[playlistMap["tracks"].toInt()].toArray();
        for(QJsonValue trackID : trackIDs)
        {
            this -> playlistHash[playlistInfo[playlistMap["name"].toInt()].toString()].push_back(QString::number(trackID.toInt()));
        }
    }
}
