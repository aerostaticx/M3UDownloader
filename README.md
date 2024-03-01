# **M3UDownloader**

Allows users to download their playlists from the iBroadcast servers as M3U playlist files. 

Use case for this app is users can manage their playlists on the iBroadcast web player, and also download the playlists as an M3U so they can play their playlists on a local storage device. Useful for cases where offline play / no phone scenario is necessary, as well as for users who do not have the premium subscription to iBroadcast, but would still like to play their playlists in full quality using the original files they have locally.

App currently only works by saving the M3U to the root directory of the local directory where music is being held. It will then structure the song reference paths in the M3U based off a chosen preset structure. File types referenced will be pulled from the iBroadcast servers, which are stored in the **same** format as when it was uploaded, provided it's a supported format. I recommend using mp3Tag to get your music organized into a supported folder structure. Example follows.

## **Example 1**

Local File Structure:  

root/

├─ myAlbum/

│  ├─ myArtist/

│  │  ├─ mySong.mp3

├─ myAlbum2/

│  ├─ myArtist2/

│  │  ├─ mySong2.flac


M3U would need to be saved at root.

## **Example 2**   

root/

├─ myArtist/

│  ├─ myAlbum/

│  │  ├─ mySong.mp3

├─ myArtist2/

│  ├─ myAlbum2/

│  │  ├─ mySong2.flac


M3U would need to be saved at root.

## **Example of what you can't do**   

root/

├─ myArtist/

│  ├─ myAlbum/

│  │  ├─ mySong.mp3

├─ myAlbum2/

│  ├─ myArtist2/

│  │  ├─ mySong2.flac

├─ mySong3.flac


This type of mix and match format is not yet supported. Use mp3Tag or similar program to organize your files!

