#ifndef CONVERSIONHANDLER_H
#define CONVERSIONHANDLER_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "library.h"
class ConversionHandler : public QObject
{
    Q_OBJECT
private:
    const Library& library;
public:
    ConversionHandler(const Library& inputLib);
    ~ConversionHandler();
public slots:
    void convert();
};
#endif // CONVERSIONHANDLER_H
