#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "Song.h"
#include <vector>
#include <string>
#include <map>

class Playlist
{
    private:
        std::string Playlist_title;
        std::vector<Song> content;

    public:
        void set_playlist_title(std::string _title);
        void add_content(Song _content);
        std::string get_playlist_title();
        void print_content();
};

#endif