#ifndef CONVERSIONHANDLER_H
#define CONVERSIONHANDLER_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include "library.h"
#include <algorithm>
#include <string>


enum conversionErrors
{
    PLAYLIST_NOT_FOUND_ERROR = 0,
};

class ConversionHandler : public QObject
{
    Q_OBJECT
    private:
        const Library& library;
        void replacementHelper(QString& inputString);
        std::unordered_map<QString,QString> MIMEhash = {  {"audio/3gpp", "*3gpp"},
                                                         {"audio/mp3", "*mp3"},
                                                         {"audio/wave", "*wav"},
                                                         {"audio/adpcm", "adp"},
                                                         {"audio/basic", "au"},
                                                         {"audio/flac", "flac"},
                                                         {"audio/midi", "kar"},
                                                         {"audio/mpeg", "m2a"},
                                                         {"audio/mpeg", "m3a"},
                                                         {"audio/mp4", "m4a"},
                                                         {"audio/midi", "mid"},
                                                         {"audio/midi", "midi"},
                                                         {"audio/mpeg", "mp2"},
                                                         {"audio/mpeg", "mp2a"},
                                                         {"audio/mpeg3", "mp3"},
                                                         {"audio/mp4", "mp4a"},
                                                         {"audio/mpeg", "mpga"},
                                                         {"audio/ogg", "oga"},
                                                         {"audio/ogg", "ogg"},
                                                         {"audio/midi", "rmi"},
                                                         {"audio/s3m", "s3m"},
                                                         {"audio/silk", "sil"},
                                                         {"audio/basic", "snd"},
                                                         {"audio/ogg", "spx"},
                                                         {"audio/wav", "wav"},
                                                         {"audio/webm", "weba"},
                                                         {"audio/xm", "xm"}};
    public:
        ConversionHandler(const Library& inputLib);
        ~ConversionHandler();
    public slots:
        void convert(QString playlistRequested, QString saveLocation, QString relativeStructure);
    signals:
        void emitConversionError(conversionErrors outputError);
};
#endif // CONVERSIONHANDLER_H
