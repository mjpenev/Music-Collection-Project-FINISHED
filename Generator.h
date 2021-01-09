#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "MusicCollection.h"
#include "Register.h"
#include "Printer.h"

class Generator
{
    public:
        void generate_playlist(std::string _username, Collection &songs, Register &users, Printer &printer);
};

#endif