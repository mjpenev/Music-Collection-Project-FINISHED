#ifndef USER_H_
#define USER_H_

#include <string>
#include <queue>
#include "Date.h"

class User
{
    private:
        std::string username;
        std::string password;
        std::string full_name;
        Date birth_date;
        std::queue<std::string> favGenres;

    public:
        void set_username(std::string _username);
        void set_password(std::string _password);
        void set_full_name(std::string _name);
        void set_birth_date(Date _date);
        void show_fav_genres(std::queue<std::string> _genres);
        void add_fav_genre(std::string _genre);
        std::string get_username();
        std::string get_password();
        std::string get_full_name();
        std::queue<std::string>& get_genres();
        Date get_date();
        void print_user();
        User();
        User(User &other);
        ~User();
       

};



#endif