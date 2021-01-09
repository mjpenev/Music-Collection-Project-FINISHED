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
int Playlist::get_size()
{
    return this->get_content().size();
}
void Playlist::print_content()
{
    if (!(this->content.empty()))
    {
        int const_size = this->content.size();
        std::queue<Song*> saver;
        for (int i = 0; i < const_size; i++)
        {
            this->content.top()->print_song();
            saver.push(this->content.top());
            this->content.pop();
        }
        while(!saver.empty())
        {
            this->content.push(saver.front());
            saver.pop();
        }
        
    }
    else
    {
        std::cout << "This playlist is currently empty" << std::endl;
    }
    
}