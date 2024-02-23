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

    std::vector<QString> getPlaylistSongs(QString playlistName) const; //returns empty if playlist doesn't exist. In case empty playlist with matching name exists, also return empty.
    std::unordered_map<QString,std::array<QString,3>> getSongHash();
public slots:
    void populateLibrary(const QJsonObject& libraryObj);
private:
    std::unordered_map<QString,QString> artistHash; //<artistID,artistName>
    std::unordered_map<QString,QString> albumHash; //<albumID,albumName>
    std::unordered_map<QString,std::array<QString,4>> songHash; //<songID : array<songName, albumName, artistName, MIMEType>>
    std::unordered_map<QString,std::vector<QString>> playlistHash; //<playlistName : vector<songID>>
};
#endif // LIBRARY_H
