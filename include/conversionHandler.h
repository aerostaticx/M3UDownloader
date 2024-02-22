#ifndef CONVERSIONHANDLER_H
#define CONVERSIONHANDLER_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
class ConversionHandler : public QObject
{
    Q_OBJECT
public:
    explicit ConversionHandler(QObject *parent = nullptr);
    ~ConversionHandler();
};
#endif // CONVERSIONHANDLER_H
