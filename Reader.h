#ifndef READER_H_
#define READER_H_

#include "MusicCollection.h"
#include "Register.h"
#include <string>

class Reader 
{
    public:
        void read_songs(Collection &songs, std::string &file_info);
        void read_users(Register &users, std::string &file_info);
};


#endif