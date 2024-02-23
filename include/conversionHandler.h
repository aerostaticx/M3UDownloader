#ifndef CONVERSIONHANDLER_H
#define CONVERSIONHANDLER_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "library.h"

enum conversionErrors
{
    PLAYLIST_NOT_FOUND_ERROR = 0,
};

class ConversionHandler : public QObject
{
    Q_OBJECT
    private:
        const Library& library;
    public:
        ConversionHandler(const Library& inputLib);
        ~ConversionHandler();
    public slots:
        void convert(QString playlistRequested, QString saveLocation, QString relativeStructure);
    signals:
        void emitConversionError(conversionErrors outputError);
};
#endif // CONVERSIONHANDLER_H
