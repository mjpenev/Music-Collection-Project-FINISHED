#ifndef PRINTER_H_
#define PRINTER_H_

#include "MusicCollection.h"
#include <string>

// Class - Console Interface

class Printer
{
    public:
        void print_start_menu();
        void print_help_command();
        void print_playlist_criterion();
        void welcome_text(std::string _username);
        void print_ready_song();
        void print_collection_start(int _size);

};

#endif