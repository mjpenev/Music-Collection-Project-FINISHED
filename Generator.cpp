#include <iostream>
#include "Generator.h"

void Generator::generate_playlist(std::string username_, Collection &songs, Register &users, Printer &printer)
{
    Playlist *curr = new Playlist;
    auto it = users.get_allUsers().begin();
    for ( ; it != users.get_allUsers().end(); it++)
    {
        if (it->first->get_username() == username_) break;
    }
    std::string playlist_title;
    std::cout << "Playlist title will be: ";
    getline(std::cin, playlist_title);
    curr->set_playlist_title(playlist_title);
    std::cout << "Max size will be (can't be more than 20): " << std::endl;
    int playlist_size;
    do
    {
        std::cin >> playlist_size;
        if (playlist_size < 0 || playlist_size > 20)
        {
            std::cout << "Invalid size!" << std::endl;
        }
    } while (playlist_size < 0 || playlist_size > 20);
    printer.print_playlist_criterion();
    std::string _criterion;
    std::cin.ignore();
    getline(std::cin, _criterion);
    std::vector<std::string> seperate_criterion;
    std::istringstream readCriteria(_criterion);
    std::string _word;
    while (readCriteria >> _word)
    {
        seperate_criterion.push_back(_word);
    }
    if (seperate_criterion.size() < 4) // if words are less than 4, then there is only 1 criteria
    {
        auto it = users.get_allUsers().begin();
        for ( ; it != users.get_allUsers().end(); it++)
        {
            if (it->first->get_username() == username_) break;
        }
        
        for (int i = 0; i < seperate_criterion.size(); i++)
        {
            
            if (seperate_criterion[i] == "Before" || seperate_criterion[i] == "After")
            {
                int year_ = 0;
                std::istringstream turnToNum(seperate_criterion[i + 1]);
                turnToNum >> year_;
                Song* curr_song = new Song;
                int counter = 0;
                for (auto iter = songs.get_songs().begin(); iter != songs.get_songs().end(); iter++)
                {
                    curr_song = *iter;
                    if (curr_song->get_year() < year_ && seperate_criterion[i] == "Before")
                    {
                        curr->add_in_playlist(curr_song);
                    }
                    else if (curr_song->get_year() >= year_ && seperate_criterion[i] == "After")
                    {
                        curr->add_in_playlist(curr_song);
                    }
                    if (counter > playlist_size) break;
                    counter++;
                }
                it->second.insert(curr);
                std::cout << "Successfully added " << curr->get_size() << " song/s to playlist!" << std::endl;
                std::cout << "Playlist with title " << playlist_title << " added in your collection!" << std::endl;           
            }
            else if (seperate_criterion[i] == "favourites")
            {

            }
            else if (seperate_criterion[i] == ">")
            {

            }
            else if (seperate_criterion[i] == "Only")
            {
                
            }
        }
        
    }
    else    // if words are more, then there are 2 combined criterion
    {
        
    }
    
    it->second.insert(curr);
};