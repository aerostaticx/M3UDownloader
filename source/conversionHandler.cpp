#include "conversionHandler.h"
ConversionHandler::ConversionHandler(const Library& l) : library(l)
{}

ConversionHandler::~ConversionHandler()
{}

void ConversionHandler::replacementHelper(QString& input)
{
    std::vector<char> dict{'<','>',':','"','/','\\','|','?','*'};
    for(char charToReplace : dict)
    {
        input.remove(charToReplace);
    }
}

void ConversionHandler::convert(QString playlistRequested, QString saveLocation, QString relativeStructure)
{
    //Handle playlist not found
    if(this -> library.getPlaylistSongs(playlistRequested).empty())
    {
        emit this -> emitConversionError(conversionErrors::PLAYLIST_NOT_FOUND_ERROR);
        return;
    }

    QFile outputFile(saveLocation + "/playlist.m3u");
    outputFile.open(QIODevice::WriteOnly);
    QTextStream out(&outputFile);

    std::vector<QString> playlistSongs = this -> library.getPlaylistSongs(playlistRequested);
    std::unordered_map<QString,std::array<QString,4>> songHash = this -> library.getSongHash();
    if(relativeStructure == "artist/album/songfile")
    {
        for(QString songID : playlistSongs)
        {
            this -> replacementHelper(songHash[songID][0]);
            out << songHash[songID][2] + '/' + songHash[songID][1] + '/' + songHash[songID][0] + '.' + this -> MIMEhash[songHash[songID][3]] << Qt::endl;
        }
    }
    else if(relativeStructure == "album/artist/songfile")
    {
        for(QString songID : playlistSongs)
        {
            this -> replacementHelper(songHash[songID][0]);
            out << songHash[songID][1] + '/' + songHash[songID][2] + '/' + songHash[songID][0] + '.' + this -> MIMEhash[songHash[songID][3]] << Qt::endl;
        }
    }
    else if(relativeStructure == "artist/songfile")
    {
        for(QString songID : playlistSongs)
        {
            this -> replacementHelper(songHash[songID][0]);
            out << songHash[songID][2] + '/' + songHash[songID][0] + '.' + this -> MIMEhash[songHash[songID][3]] << Qt::endl;
        }
    }
    else if(relativeStructure == "album/songfile")
    {
        for(QString songID : playlistSongs)
        {
            this -> replacementHelper(songHash[songID][0]);
            out << songHash[songID][1] + '/' + songHash[songID][0] + '.' + this -> MIMEhash[songHash[songID][3]] << Qt::endl;
        }
    }
    else if(relativeStructure == "songfile")
    {
        for(QString songID : playlistSongs)
        {
            this -> replacementHelper(songHash[songID][0]);
            out << songHash[songID][0] + '.' + this -> MIMEhash[songHash[songID][3]] << Qt::endl;
        }
    }
    outputFile.close();
}
