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
std::vector<std::string> System::get_words()
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

int System::get_vector_size()
{
    return words.size();
}
void System::print_content_info()
{
    this->content.get_allUsers();
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
            cout << "you just signed in" << endl;
        }
        else if (checkWord(0) == "sign" && checkWord(1) == "up")
        {
            User *curr = new User;
            std::cout << "Your username will be: " << std::endl;
            std::string _username;
            do
            {
                std::cin >> _username;
                if (_username.length() < 6)
                {
                    std::cout << "Username must be at least 6 symbols!" << std::endl;
                }
                
            } while (_username.length() < 6);
            
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
            while(!(bd->isValid(d, m, y)))
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
            }
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
            get_content().print_all_Users();
            
        }
        else if(command == "help")
        {

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
