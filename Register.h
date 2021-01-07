#ifndef REGISTER_H_
#define REGISTER_H_

#include <string>
#include <map>
#include <vector>
#include "User.h"
#include "Playlist.h"
#include <set>

class Register
{
    private:
        std::map<User*, std::set<Playlist*>> allUsers;
    public:
        void insert_in_system(std::pair<User*, std::set<Playlist*>> curr);
        void insert_playlists(std::string _username, Playlist *curr);
        void print_all_Users();
        std::map<User*, std::set<Playlist*>> &get_allUsers();
        std::set<Playlist*> &get_playlists_by_username(std::string _username);
        Register();
        ~Register();
};

#endif