#ifndef PLAYLIST_COLLECTION_H_
#define PLAYLIST_COLLECTION_H_

#include "Playlist.h"
#include <set>

class Collection
{
    private:
        std::set<Playlist*> all_playlists;
    public:
        void add_playlist(Playlist* _playlist);
        std::set<Playlist*> &get_playlists();
        void print_playlists();
};

#endif