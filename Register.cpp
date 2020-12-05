#include <iostream>
#include <vector>
#include "Register.h"
#include <map>

void Register::insert_in_system(std::pair<User*, std::vector<Playlist>> curr)
{
    this->allUsers.insert(curr);
}
std::map <User*, std::vector<Playlist>> &Register::get_allUsers()
{
    return this->allUsers;
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