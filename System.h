#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Register.h"
#include "MusicCollection.h"

class System
{
    private:
        std::vector<std::string> words;
        Register content;
        Collection music_collection;
        std::fstream file;
        std::string file_path;
        std::string file_info;
        std::string to_write;

    public:
        static System& i();
        System(const System&) = delete;
        void operator =(const System&) = delete;
        
        void _help();
        void print_content_info();
        void clearCommand();
        void run_program();
        void set_info(std::string _content);
        void set_path(std::string _path);
        void write_in_string(std::string _to_write);
        void _updateFile(std::string _path);
        void read_users(Register &users);
        void read_songs(Collection &songs);
        void push_words(std::string command);
        void set_file_info(std::string _content);

        int get_vector_size();
        Register &get_content();
        Collection &get_music_collection();
        std::string checkWord(int i);
        std::string &get_info();
        std::string &get_path();
        std::string &get_file_info();
        std::vector<std::string> &get_words();

        System();
        ~System();

};

#endif