#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "MusicCollection.h"
#include "Register.h"
#include "Printer.h"
#include <fstream>

class Generator
{
    public:
        void generate_playlist(std::string username_, Collection &songs, Register &users, Printer &printer, std::string &file_info, std::string &path_);
};

#endif