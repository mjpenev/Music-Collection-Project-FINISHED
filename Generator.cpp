#include <iostream>
#include "Generator.h"

void Generator::generate_playlist(std::string username_, Collection &songs, Register &users, Printer &printer, std::string &file_info, std::string &path_)
{
    Playlist *curr = new Playlist;
    int max_capacity = 0;
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
    if (_criterion == "From favourites")
    {
        auto it = users.get_allUsers().begin();
        for ( ; it != users.get_allUsers().end() ; it++)
        {
            if (it->first->get_username() == username_) break;
        }
        auto iter = songs.get_songs().begin();
        int const_size = it->first->get_genres().size();
        Song* curr_song = new Song;
        for ( ; iter != songs.get_songs().end(); iter++)
        {
            curr_song = *iter;
            for (int i = 0; i < const_size; i++)
            {
                if (max_capacity >= playlist_size) break;
                if (it->first->get_genres().front() + " " == curr_song->get_genre())
                {
                    curr->add_in_playlist(curr_song);
                    max_capacity++;
                }
                it->first->get_genres().push(it->first->get_genres().front());
                it->first->get_genres().pop();
            }
            
        }
        if (curr->get_size() != 0)
        {
            std::cout << "Successfully added " << curr->get_size() << " song/s to playlist from FAVOURITE GENRES criteria!" << std::endl;
            std::cout << "Playlist with title " << playlist_title << " added in your collection!" << std::endl; 
        }
        else
        {
            std::cout << "Playlist is still empty! There are no songs fulfilling criteria!" << std::endl;
        }
        
    }
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
                for (auto iter = songs.get_songs().begin(); iter != songs.get_songs().end(); iter++)
                {
                    if (max_capacity >= playlist_size) break;
                    curr_song = *iter;
                    if (curr_song->get_year() < year_ && seperate_criterion[i] == "Before")
                    {
                        curr->add_in_playlist(curr_song);
                        max_capacity++;
                    }
                    else if (curr_song->get_year() >= year_ && seperate_criterion[i] == "After")
                    {
                        curr->add_in_playlist(curr_song);
                        max_capacity++;
                    }
                }
                it->second.insert(curr);
                std::cout << "Successfully added " << curr->get_size() << " song/s to playlist from YEAR CRITERIA!" << std::endl;
                std::cout << "Playlist with title " << playlist_title << " added in your collection!" << std::endl;           
            }
            else if (seperate_criterion[i] == ">")
            {
                if (max_capacity >= playlist_size) break;
                int rating_ = 0;
                std::string num = seperate_criterion[i + 1];
                std::istringstream turnToNum(num);
                turnToNum >> rating_;
                auto iter = songs.get_songs().begin();
                Song *curr_song;
                for ( ; iter != songs.get_songs().end(); iter++)
                {
                    curr_song = *iter;
                    if (curr_song->get_rating() >= rating_)
                    {
                        curr->add_in_playlist(curr_song);
                    }
                }
                if (curr->get_size() != 0)
                {
                    std::cout << "Successfully added " << curr->get_size() << " song/s to playlist from FAVOURITE GENRES criteria!" << std::endl;
                    std::cout << "Playlist with title " << playlist_title << " added in your collection!" << std::endl; 
                }
                else
                {
                    std::cout << "Playlist is still empty! There are no songs fulfilling criteria!" << std::endl;
                }
                
            }
            else if (seperate_criterion[i] == "Only")
            {
                if (max_capacity >= playlist_size) break;
                auto iter = songs.get_songs().begin();
                Song *curr_song;
                for ( ; iter != songs.get_songs().end(); iter++)
                {
                    curr_song = *iter;
                    if (curr_song->get_genre() == seperate_criterion[i + 1] + " ")
                    {
                        curr->add_in_playlist(curr_song);
                    }
                }
                if (curr->get_size() != 0)
                {
                    std::cout << "Successfully added " << curr->get_size() << " song/s to playlist from ONLY GENRE criteria!" << std::endl;
                    std::cout << "Playlist with title " << playlist_title << " added in your collection!" << std::endl; 
                }
                else
                {
                    std::cout << "Playlist is still empty! There are no songs fulfilling criteria!" << std::endl;
                }
                
            }
        }
        
    }
    else 
    {
        std::cout << "Invalid criterion!" << std::endl;
    }
    
    it->second.insert(curr);
    std::string file_add_songs;
    std::queue<Song*> helper;
    int const_size = curr->get_content().size();
    for (int i = 0; i < const_size; i++)
    {
        file_add_songs += curr->get_content().top()->get_title();
        file_add_songs += " / ";
        helper.push(curr->get_content().top());
        curr->get_content().pop();
    }
    while (!helper.empty())
    {
        curr->get_content().push(helper.front());
        helper.pop();
    }
    std::string file_insertion = "Playlist: " + playlist_title + " In " + username_ + " 's collection has " + "Capacity: " + std::to_string(curr->get_size()) +  "\n"
    + "Contains: " + file_add_songs + "| \n";
    std::ofstream updatePlaylist(path_);
    file_info += file_insertion;
    updatePlaylist << file_info;

};