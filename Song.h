#ifndef SONG_H_
#define SONG_H_

#include <string>
#include <vector>

class Song
{
    private:
        std::string title;
        std::string artist;
        std::string genre;
        std::string album;
        int year;
        int rate_helper;
        std::vector<std::string> people_who_rated;
        int people_who_rate;
        double rating;
    
    public:
        void set_title(std::string _title);
        void set_artist(std::string _artist);
        void set_genre(std::string _genre);
        void set_album(std::string _album);
        void set_year(int _year);
        void set_people(int _num);
        void set_helper(int _num);
        void set_rating(double _rating);
        void push_person(std::string _name);
        std::string get_title();
        std::string get_artist();
        std::string get_genre();
        std::string get_album();
        std::vector<std::string>& get_names();
        int get_year();
        int get_helper();
        double get_rating();
        int get_people();
        void print_song();

        Song();
        ~Song();
        
};


#endif