#ifndef SONG_H_
#define SONG_H_

#include <string>

class Song
{
    private:
        std::string title;
        std::string artist;
        std::string genre;
        std::string album;
        int year;
        double rating;
    
    public:
        void set_title(std::string _title);
        void set_artist(std::string _artist);
        void set_genre(std::string _genre);
        void set_album(std::string _album);
        void set_year(int _year);
        void set_rating(double _rating);
        std::string get_title();
        std::string get_artist();
        std::string get_genre();
        std::string get_album();
        int get_year();
        double get_rating();
        void print_song();

        Song();
        ~Song();
        
};


#endif