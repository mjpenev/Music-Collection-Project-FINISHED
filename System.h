#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <vector>
#include <string>
#include "Register.h"
#include "MusicCollection.h"

class System
{
    private:
        std::vector<std::string> words;
        Register content;
        Collection music_collection;

    public:
        static System& i();
        System(const System&) = delete;
        void operator =(const System&) = delete;

        System();
        ~System();
        
        void _help();
        void print_content_info();
        Register &get_content();
        Collection &get_music_collection();
        void push_words(std::string command);
        std::string checkWord(int i);
        std::vector<std::string> &get_words();
        int get_vector_size();
        void clearCommand();
        void run_program();

};

#endif