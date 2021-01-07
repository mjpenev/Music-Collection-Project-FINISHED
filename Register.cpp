#include <iostream>
#include <vector>
#include "Register.h"
#include <map>
#include <set>

void Register::insert_in_system(std::pair<User*, std::set<Playlist*>> curr)
{
    this->allUsers.insert(curr);
}
std::map <User*, std::set<Playlist*>> &Register::get_allUsers()
{
    return this->allUsers;
}
std::set<Playlist*> &Register::get_playlists_by_username(std::string _username)
{   
    bool success = false;
    auto it = get_allUsers().begin();
    for ( ; it != get_allUsers().end(); it++)
    {
        if (it->first->get_username() == _username)
        {
            return it->second;
        }

    }
    
}
void Register::insert_playlists(std::string _username, Playlist *curr)
{
    auto it = this->allUsers.begin();
    for ( ; it != this->allUsers.end(); it++)
    {
        if (it->first->get_username() == _username)
        {
            it->second.insert(curr);
            break;
        }
    }
    
}
void Register::print_all_Users()
{
    for (auto it = get_allUsers().begin(); it != get_allUsers().end(); it++)
    {
        it->first->print_user();
    }

}
Register::Register()
{

}
Register::~Register()
{

}