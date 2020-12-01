#include <iostream>
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
void User::show_fav_genres(std::vector<std::string> _genres)
{
    for (int i = 0; i < _genres.size(); i++)
    {
        std::cout << _genres[i] << std::endl;
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
void User::print_user()
{
    std::cout << "=================================" << std::endl;
    std::cout << "Username: " << this->username << std::endl;
    std::cout << "Password: " << this->password << std::endl;
    std::cout << "Full name: " << this->full_name << std::endl;
    std::cout << "Birth-date: "; this->get_date().printDate();
    std::cout << "=================================" << std::endl;
}

User::User() : username(""), password(""), full_name("")
{

}
User::~User()
{

}
