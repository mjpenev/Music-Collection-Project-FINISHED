#include "Playlist.h"
#include "Song.h"

void Playlist::set_playlist_title(std::string _title)
{
    this->Playlist_title = _title;
}
void Playlist::add_content(Song _content)
{
    this->content.push_back(_content);
}
std::string Playlist::get_playlist_title()
{
    return this->Playlist_title;
}
void Playlist::print_content()
{
    for (int i = 0; i < content.size(); i++)
    {
        content[i].print_song();
    }
    
}