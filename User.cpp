#include <iostream>
#include <string>
#include "User.h"
#include "Date.h"

void User::set_username(std::string _username)
{
    this->username = _username;
}
void User::set_password(std::string _password)
{
    this->password = _password;
}
void User::set_full_name(std::string _name)
{
    this->full_name= _name;
}
void User::set_birth_date(Date _date)
{
    this->birth_date = _date;
}
void User::show_fav_genres(std::queue<std::string> _genres)
{
    for (int i = 0; i < this->favGenres.size(); i++)
    {
        favGenres.push(favGenres.front());
        if (i > 0)
        {
            std::cout << ", ";
        }
        std::cout << favGenres.front();
        favGenres.pop();
    }
    
}
std::string User::get_username()
{
    return this->username;
}
std::string User::get_password()
{
    return this->password;
}
std::string User::get_full_name()
{
    return this->full_name;
}
Date User::get_date()
{
    return this->birth_date;
}
void User::add_fav_genre(std::string _genre)
{
    this->favGenres.push(_genre);
}
std::queue<std::string>& User::get_genres()
{
    return this->favGenres;
}
void User::print_user()
{
    int counter = this->password.length();
    std::cout << "=================================" << std::endl;
    std::cout << "Username: " << this->username << std::endl;
    std::cout << "Password: "; while (counter != 0) { counter--; std::cout << "*"; } std::cout << std::endl;
    std::cout << "Full name: " << this->full_name << std::endl;
    std::cout << "Birth-date: "; this->get_date().printDate();
    std::cout << "Favourite genres: "; if (this->favGenres.empty()) { std::cout << "List of favourite genres is currently empty!" << std::endl;}
    else { show_fav_genres(this->favGenres);} std::cout << std::endl;
    std::cout << "=================================" << std::endl;
}
User::User() :  username(""), password(""), full_name(""), birth_date() 
{

}
User::User(User &other)
{
    this->username = other.username;
    this->password = other.password;
    this->full_name = other.full_name;
    this->birth_date = other.birth_date;
}
User::~User()
{

}
