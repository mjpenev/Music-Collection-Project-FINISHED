#include <iostream>
#include <map>
#include "System.h"
#include "Playlist.h"
#include "Song.h"
#include <set>
#include <queue>

System& System::i()
{
    static System instance;
    return instance;
}
System::System() 
{

}
void System::push_words(std::string _command)
{
    this->words.push_back(_command);
}
std::vector<std::string> &System::get_words()
{
    return this->words;
}
std::string System::checkWord(int i)
{
    return this->words[i];
}
Register &System::get_content()
{
    return this->content;
}
Printer &System::get_printer()
{
    return this->printer;
}
void System::clearCommand()
{
    this->words.clear();
}
void System::_help()
{
    this->printer.print_help_command();
}
int System::get_vector_size()
{
    return words.size();
}
void System::print_content_info()
{
    get_content().print_all_Users();   
}
Collection &System::get_music_collection()
{
    return this->music_collection;
}
void System::set_path(std::string _path)
{
    this->file_path = _path;
}
std::string &System::get_path()
{
    return this->file_path;
}
void System::set_file_info(std::string _content)
{
    this->file_info = _content;
}
std::string &System::get_file_info()
{
    return this->file_info;
}
void System::set_file_end()
{
    int final_index = this->get_file_info().length();
    for (int i = 0; i < final_index; i++)
    {
        if (get_file_info()[i] == '*')
        {
            get_file_info().erase(i, 1);
        }
    }
    std::ofstream setStar(this->file_path);
    get_file_info() += "*";
    setStar << get_file_info();
}
void System::run_program()
{
    std::string command;
    this->printer.print_start_menu();
    set_path("C:\\Users\\User\\desktop\\test.txt");
    this->file.open(get_path(), std::ios::in);
    getline(this->file, this->file_info, '*');
    this->reader.read_songs(this->get_music_collection(), this->get_file_info());
    this->reader.read_users(this->get_content(), this->get_file_info());
    if (file.is_open())
    {
        std::cout << "Successfully opened file!" << std::endl;
    }
    else
    {
        std::cout << "A problem occured in opening file!" << std::endl;
    }
    std::cout << std::endl;
    while(command != "exit")
    {
        std::cout << "Insert command: " << std::endl;
        getline(std::cin, command);
        std::istringstream lineIn(command);
        std::string word;
        while (lineIn >> word)
        {
            push_words(word);
        }
        if (checkWord(0) == "sign" && checkWord(1) == "in")
        {
            if (get_content().get_allUsers().empty())
            {
                std::cout << "No registered users yet!" << std::endl;
            }
            else
            {
                std::string _username;
                std::string _password;
                do
                {
                    std::cout << "Username: ";
                    std::cin >> _username;
                    if (_username.length() < 6)
                    {
                        std::cout << "Username must be at least 6 symbols!" << std::endl;
                    }
                } while (_username.length() < 6);
                do
                {
                    std::cout << "Password: ";
                    std::cin >> _password;
                    if (_password.length() < 6)
                    {
                        std::cout << "Password must be at least 6 symbols!" << std::endl;
                    }
                } while (_password.length() < 6);
                bool checkUser = false;
                for (auto it = get_content().get_allUsers().begin(); it != get_content().get_allUsers().end(); it++)
                {
                    if (it->first->get_username() == _username && it->first->get_password() == _password)
                    {
                        checkUser = true;
                    }

                }
                if (checkUser)
                {
                    this->printer.welcome_text(_username);
                }
                else
                {
                    std::cout << "Invalid username or password! Please try again. If you're not registered yet type 'sign up' !" << std::endl;
                }
                std::cin.ignore();
                std::string new_command; 
                while (new_command != "sign out")
                {
                    if (!checkUser) break;
                    std::cout << "You're logged as " << _username << ". Insert your command: ";
                    getline(std::cin, new_command);
                    if (new_command == "sign out")
                    {
                        std::cout << "Signing out! See you next time!" << std::endl;
                    }
                    else if (new_command == "add genre")
                    {
                        call.add_genre(_username, this->get_content(), this->get_path(), this->get_file_info());
                        set_file_end();
                    }
                    else if (new_command == "remove genre")
                    {
                        call.remove_genre(_username, this->get_content(), this->get_path(), this->get_file_info());
                        set_file_end();
                    }
                    else if(new_command == "add song")
                    {
                        call.add_song(this->get_file_info(), this->get_printer(), this->get_music_collection(), this->get_path());
                        set_file_end();
                    }
                    else if (new_command == "generate playlist")
                    {
                        this->generator.generate_playlist(_username, this->get_music_collection(), this->get_content(), this->get_printer());
                    }
                    else if (new_command == "show playlist")
                    {
                        call.show_playlist(_username, this->get_content());
                    }
                    else if (new_command == "show collection")
                    {
                        call.show_collection(this->get_music_collection(), this->get_printer());
                    }
                    else if(new_command == "show users")
                    {
                        call.show_users(this->get_content()); 
                    }
                    else if(new_command == "rate song")
                    {
                        call.rate_song(_username, this->get_path(), this->get_file_info(), this->get_music_collection());
                        set_file_end();
                    }
                    else if (new_command == "help")
                    {
                        _help();
                    }
                    else if (new_command == "exit")
                    {
                        std::cout << "Sign out first with the 'sign out' command!" << std::endl;
                    }
                    else
                    {
                        std::cout << "You entered incorrect command. Try again. To see supported commands type 'help'" << std::endl;
                    }
                }
            }
        }
        else if (checkWord(0) == "sign" && checkWord(1) == "up")
        {
            call.sign_up(this->get_content(), this->get_path(), this->get_file_info());
            set_file_end();
        }
        else if(checkWord(0) == "show" && checkWord(1) == "collection")
        {
            call.show_collection(this->get_music_collection(), this->get_printer());
        }
        else if(checkWord(0) == "show" && checkWord(1) == "users")
        {
            call.show_users(this->get_content());  
        }
        else if(command == "help")
        {
            _help();
        }
        else if (command != "exit")
        {
            std::cout << "You entered incorrect command. Try again. To see supported commands type 'help'" << std::endl;
        }
        clearCommand();
        lineIn.clear();
    }

}

System::~System()
{
    if (file.is_open())
    {
        file.close();
    }
    std::cout << "Closing files. Exiting program..." << std::endl;
}
