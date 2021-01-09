#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "Song.h"
#include <string>
#include <queue>
#include <vector>

class Playlist
{
    private:
        std::string Playlist_title;
        std::priority_queue<Song*> content;    
    public:
        void set_playlist_title(std::string _title);
        void add_in_playlist(Song* _song);
        std::string get_playlist_title();
        std::priority_queue<Song*> &get_content();
        int get_size();
        void print_content();

};


#endif