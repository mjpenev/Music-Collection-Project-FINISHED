#ifndef REGISTER_H_
#define REGISTER_H_

#include <string>
#include <map>
#include <vector>
#include "User.h"
#include "Playlist.h"

class Register
{
    private:
        std::map<User*, std::vector<Playlist>> allUsers;
    public:
        void insert_in_system(std::pair<User*, std::vector<Playlist>> curr);
        void print_all_Users();
        void trace_all_playlists();
        std::map<User*, std::vector<Playlist>> &get_allUsers();
        Register();
        ~Register();
};

#endif