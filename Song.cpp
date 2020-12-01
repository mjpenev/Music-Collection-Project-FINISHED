#include <iostream>
#include "Song.h"


void Song::set_title(std::string _title) 
{
    this->title = _title;
}
void Song::set_artist(std::string _artist)
{
    this->artist = _artist;
}
void Song::set_genre(std::string _genre)
{
    this->genre = _genre;
}
void Song::set_album(std::string _album)
{
    this->album = _album;
}
void Song::set_year(int _year)
{
    this->year = _year;
}
void Song::set_rating(double _rating)
{
    this->rating = _rating;
}
std::string Song::get_title()
{
    return this->title;
}
std::string Song::get_artist()
{
    return this->artist;
}
std::string Song::get_genre()
{
    return this->genre;
}
std::string Song::get_album()
{
    return this->album;
}
int Song::get_year()
{
    return this->year;
}
double Song::get_rating()
{
    return this->rating;
}
void Song::print_song()
{
    std::cout << "=====================================" << std::endl;
    std::cout << "Song title: " << this->title << std::endl;
    std::cout << "Song performed by: " << this->artist << std::endl;
    std::cout << "Album: " << this->album <<std::endl;
    std::cout << "Song genre: " << this->genre << std::endl;
    std::cout << "Year of release: " << this->year << std::endl;
    std::cout << "Rating: " << this->rating << std::endl;
    std::cout << "=====================================" << std::endl;
}

Song::Song() : title("Unknown"), artist("Unknown"), genre("Unknown"), album("Unknown"), year(0), rating(0)
{

}
Song::~Song()
{

}