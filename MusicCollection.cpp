#include "MusicCollection.h"
#include <iostream>

void Collection::add_song(Song *_song)
{
    this->all_songs.insert(_song);
}
std::set<Song*> &Collection::get_songs()
{
    return this->all_songs;
}
void Collection::print_songs()
{
    if (this->all_songs.empty())
    {
        std::cout << "Music collection is currently empty! You can add some songs by the 'add song' command." << std::endl;
    }
    else
    {
        for (auto it = this->all_songs.begin(); it != this->all_songs.end(); it++)
        {
            Song* curr;
            curr = *it;
            curr->print_song();
            std::cout << std::endl;
        }
                
    }

}