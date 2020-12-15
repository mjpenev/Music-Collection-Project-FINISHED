#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "Song.h"
#include <vector>
#include <string>
#include <set>

class Playlist
{
    private:
        std::string Playlist_title;
        std::set<Song*> content;    

    public:
        void set_playlist_title(std::string _title);
        void add_song(Song* _song);
        std::string get_playlist_title();
        std::set<Song*> &get_content();
        int content_size();
        void print_content();
};

#endif