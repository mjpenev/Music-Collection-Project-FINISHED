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
void Playlist::add_in_playlist(Song* _song)
{
    this->content.push(_song);
}
std::priority_queue<Song*> &Playlist::get_content()
{
    return this->content;
}
int Playlist::content_size()
{
    return this->content.size();
}
void Playlist::print_content()
{
    if (!(this->content.empty()))
    {
        for (int i = 0; i < this->content.size(); i++)
        {
            this->content.push(this->content.top());
            this->content.top()->print_song();
            this->content.pop();
        }
        
    }
    else
    {
        std::cout << "This playlist is currently empty" << std::endl;
    }
    
}