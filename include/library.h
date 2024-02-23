#ifndef LIBRARY_H
#define LIBRARY_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject *parent = nullptr);
    ~Library();

    std::unordered_map<QString,std::vector<QString>> getPlaylistHash();
    std::unordered_map<QString,std::array<QString,3>> getSongHash();
public slots:
    void populateLibrary(const QJsonObject& libraryObj);
private:
    std::unordered_map<QString,QString> artistHash; //<artistID,artistName>
    std::unordered_map<QString,QString> albumHash; //<albumID,albumName>
    std::unordered_map<QString,std::array<QString,3>> songHash; //<songID : array<songName, albumName, artistName>>
    std::unordered_map<QString,std::vector<QString>> playlistHash; //<playlistName : vector<songID>>
};
#endif // LIBRARY_H
