#ifndef MUSIC_COLLECTION_H_
#define MUSIC_COLLECTION_H_

#include "Song.h"
#include <set>

class Collection
{
    private:
        std::set<Song*> all_songs;
    public:
        void add_song(Song* _song);
        std::set<Song*> &get_songs();
        void print_songs();
};

#endif