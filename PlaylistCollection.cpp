#include "PlaylistCollection.h"
#include <iostream>

void Collection::add_playlist(Playlist *_playlist)
{
    this->all_playlists.insert(_playlist);
}
std::set<Playlist*> &Collection::get_playlists()
{
    return this->all_playlists;
}
void Collection::print_playlists()
{
    if (this->all_playlists.empty())
    {
        std::cout << "Music collection is currently empty! You can add some playlist by the 'generate playlist' command." << std::endl;
    }
    else
    {
        for (auto it = this->all_playlists.begin(); it != this->all_playlists.end(); it++)
        {
            std::cout << "=========================================" << std::endl;
            std::cout << std::endl;
            Playlist *curr = *it;
            std::cout << "The Playlist with title '" << curr->get_playlist_title() << "'" << "contains - " << curr->content_size() << " songs" << std::endl;
            std::cout << std::endl;
            std::cout << "=========================================" << std::endl;
        }
    }
    
    
    
}