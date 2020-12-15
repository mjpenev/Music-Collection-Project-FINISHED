#include "Playlist.h"
#include "Song.h"
#include <iostream>

void Playlist::set_playlist_title(std::string _title)
{
    this->Playlist_title = _title;
}
std::string Playlist::get_playlist_title()
{
    return this->Playlist_title;
}
void Playlist::add_song(Song* _song)
{
    this->content.insert(_song);
}
std::set<Song*> &Playlist::get_content()
{
    return this->content;
}
int Playlist::content_size()
{
    int size = 0;

    for (auto it = get_content().begin(); it != get_content().end(); it++)
    {
        size++;
    }

    return size;
}
void Playlist::print_content()
{
    if (!(this->content.empty()))
    {
        for (auto it = get_content().begin(); it != get_content().end(); it++)
        {
            Song *curr = new Song;
            curr = *it;
            curr->print_song();
        }
        
    }
    else
    {
        std::cout << "This playlist is currently empty" << std::endl;
    }
    
}