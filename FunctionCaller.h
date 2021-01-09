#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "MusicCollection.h"
#include "Register.h"
#include "Printer.h"
#include <fstream>

class Functions
{
    public:
        void add_genre(std::string _username, Register &users, std::string &path_, std::string &file_info);
        void remove_genre(std::string _username, Register &users, std::string &path_, std::string &file_info);
        void add_song(std::string &file_info, Printer &printer, Collection &songs, std::string &path_);
        void show_playlist(std::string _username, Register &users);
        void rate_song(std::string _username, std::string &path_, std::string &file_info, Collection &songs);
        void sign_up(Register &users, std::string &path_, std::string &file_info);
};
#endif