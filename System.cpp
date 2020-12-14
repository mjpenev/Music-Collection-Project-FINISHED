#include <iostream>
#include <sstream>
#include <map>
#include "System.h"
#include "Playlist.h"
#include "Song.h"

using namespace std;

System& System::i()
{
    static System instance;
    return instance;
}

System::System() 
{

}

void System::push_words(string _command)
{
    this->words.push_back(_command);
}
std::vector<std::string> &System::get_words()
{
    return this->words;
}
string System::checkWord(int i)
{
    return this->words[i];
}
Register &System::get_content()
{
    return this->content;
}
void System::clearCommand()
{
    this->words.clear();
}

void System::_help()
{
    std::cout << "====================   List of all supported commands   ====================" << std::endl;
    std::cout << std::endl;
    std::cout << "- sign up - Makes a new registration in the system." << std::endl;
    std::cout << "- sign in - Signs in the system with already made registration." << std::endl;
    std::cout << "- show users - Shows a list with information for all users." << std::endl;
    std::cout << "- open <file path> - Opens a file with registrations and reads information." << std::endl;
    std::cout << "- close - Closes a file." << std::endl;
    std::cout << "- save - Saves all changes to the opened file." << std::endl;
    std::cout << "- help - Shows a list with supported commands." << std::endl;
    std::cout << "- exit - Closing files and exiting program." << std::endl;
    std::cout << std::endl;
    std::cout << "====================   Once you've logged in you can   =====================" << std::endl;
    std::cout << std::endl;
    std::cout << "- add playlist <playlist> - Adds playlist to User's favourites."<<std::endl;
    std::cout << "- add favourite genre <genre> - Adds genre to User's favourites." << std::endl;
    std::cout << std::endl;
    std::cout << "============================================================================" << std::endl;
}

int System::get_vector_size()
{
    return words.size();
}
void System::print_content_info()
{
    get_content().print_all_Users();   
}

void System::run_program()
{
    string command;
    cout << "*********************************************************" << endl;
    cout << endl;
    cout << "*********" << " WELCOME TO YOUR MUSIC COLLECTION APP! " << "*********" << endl;
    cout << endl;
    cout << "*********************************************************" << endl;
    cout << endl;
    cout << "   " << "YOU CAN REGISTER IN OUR SYSTEM BY TYPING 'sign up'" << "   "
    << endl << "   "<< "   FOR ALREADY REGISTERED ACCOUNTS USE 'sign in'" << "     " << endl;
    cout << endl;
    cout << "*********************************************************" << endl;


    while(command != "exit")
    {
        cout << "Insert command: " << endl;
        getline(cin, command);
        istringstream lineIn(command);
        string word;
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
                    std::cout << "======================================" << std::endl;
                    std::cout << std::endl;
                    std::cout << "           Welcome, " << _username << "!" << std::endl;
                    std::cout << std::endl;
                    std::cout << "======================================" << std::endl;
                }
                else
                {
                    std::cout << "Invalid username or password! Please try again. If you're not registered yet type 'sign up' !" << std::endl;
                }
                cin.ignore();
                std::string new_command; 
                while (new_command != "sign out")
                {
                    std::cout << "You're logged as " << _username << ". Insert your command: ";
                    getline(cin, new_command);
                    if (new_command == "sign out")
                    {
                        std::cout << "Signing out! See you next time!" << std::endl;
                    }
                    else if (new_command == "add genres")
                    {
                        auto it = get_content().get_allUsers().begin();
                        for (; it != get_content().get_allUsers().end(); it++)
                        {
                            if (it->first->get_username() == _username)
                            {
                                break;
                            }
                        }
                        std::cout << "==========================================================================" << std::endl;
                        std::cout << std::endl;
                        std::cout << "Example: pop rock rnb jazz blues reggae country...";
                        std::cout << std::endl;
                        std::cout << "Add these genres to favourite: ";
                        std::string genres_to_add;
                        getline(cin, genres_to_add);
                        std::vector<std::string> seperate_genres;
                        
                        istringstream streams(genres_to_add);
                        std::string gen;
                        while(streams >> gen)
                        {
                            seperate_genres.push_back(gen);
                        }
                        for (int i = 0; i < seperate_genres.size(); i++)
                        {
                            it->first->add_fav_genre(seperate_genres[i]);
                            it->first->add_fav_genre(" ");
                        }
                        
                        std::cout << "Genre/s successfully added to favourites!" << std::endl;

                    }
                    else if (new_command == "add playlists")
                    {
                        std::cout << "okay playlist" << std::endl;
                    }
                    else if (new_command == "help")
                    {
                        _help();
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
            User *curr = new User;
            std::string _username;
            bool checkName = true;
            do
            {
                checkName = true;
                std::cout << "Your username will be: " << std::endl;
                std::cin >> _username;
                if (_username.length() < 6)
                {
                    std::cout << "Username must be at least 6 symbols!" << std::endl;
                }
                if (!(get_content().get_allUsers().empty()))
                {
                    for (auto it = get_content().get_allUsers().begin(); it != get_content().get_allUsers().end(); it++)
                    {
                        if (it->first->get_username() == _username)
                        {
                            checkName = false;
                            std::cout << "A user with the same nickname is already registered! Try again." << std::endl;
                        }
                    }
                    
                }

            } while (_username.length() < 6 || !checkName);
            curr->set_username(_username);

            std::cout << "Type your password: " << std::endl;
            std::string _password;
            do
            {
                std::cin >> _password;
                if (_password.length() < 6)
                {
                    std::cout << "Password must be at least 6 symbols!" << std::endl;
                }
            } while (_password.length() < 6);

            curr->set_password(_password);

            std::string _fullname , first, surname, last;
            std::cout << "Your first name is: ";
            std::cin >> first;
            std::cout << "Your surname name is: ";
            std::cin >> surname;
            std::cout << "Your family name is: ";
            std::cin >> last;
            _fullname = first + " " + surname + " " + last;
            curr->set_full_name(_fullname);
            
            std::cout << "Your birth date: " << std::endl;
            Date *bd = new Date;
            int d, m, y;
            do
            {
                std::cout << "Day: ";
                std::cin >> d;
                std::cout << "Month: ";
                std::cin >> m;
                std::cout << "Year: ";
                std::cin >> y;
                if (!(bd->isValid(d, m, y)))
                {
                    std::cout << "Incorrect date! Please, try again." << std::endl;
                }
            } while (!(bd->isValid(d, m, y)));
            bd->setDay(d);
            bd->setMonth(m);
            bd->setYear(y);
            cin.ignore();
            curr->set_birth_date(*(bd));

            std::pair<User*, std::vector<Playlist>> current;
            current.first = curr;
            std::vector<Playlist> songs;
            current.second = songs;
            get_content().insert_in_system(current);
            std::cout << "Registration is succesfully made! Type 'sign in' to log into your account!" << std::endl;         
        }
        else if(checkWord(0) == "show" && checkWord(1) == "users")
        {
            if (this->get_content().get_allUsers().empty())
            {
                std::cout << "No registered users yet!" << std::endl;
            }
            get_content().print_all_Users();   
        }
        else if(command == "help")
        {
            _help();
        }
        else if (command != "exit")
        {
            cout << "You entered incorrect command. Try again. To see supported commands type 'help'" << endl;
        }
        clearCommand();
        lineIn.clear();
    }

}

System::~System()
{
    cout << "Closing files. Exiting program..." << endl;
}
