#include "conversionHandler.h"

ConversionHandler::ConversionHandler(const Library& l) : library(l)
{}

ConversionHandler::~ConversionHandler()
{}

void ConversionHandler::convert(QString playlistRequested, QString saveLocation, QString relativeStructure)
{
    //Handle playlist not found
    if(this -> library.getPlaylistSongs(playlistRequested).empty())
    {
        qInfo() << "Playlist doesn't exist!";
    }
}
