#include <iostream>
#include <sstream>
#include <map>
#include "System.h"
#include "Playlist.h"
#include "PlaylistCollection.h"
#include "Song.h"
#include <set>

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
    std::cout << "- generate playlist -  Generates new playlist. "<<std::endl;
    std::cout << "- add song -  Generates song and adds it in playlist. "<<std::endl;
    std::cout << "- show users - Shows a list with information for all users." << std::endl;
    std::cout << "- show collection - Shows a list with information for all playlists." << std::endl;
    std::cout << "- help - Shows a list with supported commands." << std::endl;
    std::cout << "- exit - Closing files and exiting program." << std::endl;
    std::cout << std::endl;
    std::cout << "====================   Once you've logged in you can   =====================" << std::endl;
    std::cout << std::endl;
    std::cout << "- add genres - Adds genre to User's favourites." << std::endl;
    std::cout << "- sign out - Signs out from account." << std::endl;
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
Collection &System::get_music_collection()
{
    return this->music_collection;
}

void System::run_program()
{
    string command;
    std::cout << "*********************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << "*********" << " WELCOME TO YOUR MUSIC COLLECTION APP! " << "*********" << std::endl;
    std::cout << std::endl;
    std::cout << "*********************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << "   " << "YOU CAN REGISTER IN OUR SYSTEM BY TYPING 'sign up'" << "   "
    << std::endl << "   "<< "   FOR ALREADY REGISTERED ACCOUNTS USE 'sign in'" << "     " << std::endl;
    std::cout << "           TO SEE SUPPORTED COMMANDS TYPE 'help' " << std::endl;
    std::cout << std::endl;
    std::cout << "*********************************************************" << std::endl;


    while(command != "exit")
    {
        std::cout << "Insert command: " << endl;
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

            std::pair<User*, std::set<Playlist>> current;
            current.first = curr;
            std::set<Playlist> songs;
            current.second = songs;
            get_content().insert_in_system(current);
            std::cout << "Registration is succesfully made! Type 'sign in' to log into your account!" << std::endl;         
        }
        else if(checkWord(0) == "generate" && checkWord(1) == "playlist")
        {
            Playlist *curr = new Playlist;
            std::string _title;
            std::cout << "Name the new playlist: ";
            getline(cin , _title);
            curr->set_playlist_title(_title);
            get_music_collection().add_playlist(curr);
            std::cout << "Playlist successfully added to Music collection!" << std::endl;
        }
        else if(checkWord(0) == "show" && checkWord(1) == "collection")
        {
            get_music_collection().print_playlists();
        }
        else if(checkWord(0) == "add" && checkWord(1) == "song")
        {
            if (get_music_collection().get_playlists().empty())
            {
                std::cout << "Collection is empty yet. You must generate a playlist first!" << std::endl;
            }
            else
            {
                Song *curr = new Song;
                std::string _album, _artist, _genre, _rating, _title, _playlist;
                int _year;
                cout << "Title of the song: ";
                getline(cin, _title);
                curr->set_title(_title);
                cout << "Name the artist: ";
                getline(cin, _artist);
                curr->set_artist(_artist);
                cout << "Album (not necessary) : ";
                getline(cin, _album);
                curr->set_album(_album);
                cout << "Genre of song: ";
                cin >> _genre;
                curr->set_genre(_genre);
                cin.ignore();
                do
                {
                    std::cout << "Year of release: ";
                    cin >> _year;
                } while (_year < 0 || _year > 2020);
                cin.ignore();
                curr->set_year(_year);
                std::cout << "************************************************************************************************" <<std::endl;
                std::cout << std::endl;
                std::cout << "You're song is ready! Now which playlist do you choose? To see playlists type (show collection)." << std::endl;
                std::cout << std::endl;
                std::cout << "************************************************************************************************" <<std::endl;
                bool success = false;
                while (!success)
                {
                    std::cout << "Playlist title: ";
                    getline(cin, _playlist);
                    for (auto it = get_music_collection().get_playlists().begin(); it != get_music_collection().get_playlists().end(); it++)
                    {
                        Playlist* curr_playlist;
                        curr_playlist = *it;
                        if (curr_playlist->get_playlist_title() == _playlist)
                        {
                            curr_playlist->add_song(curr);
                            success = true;
                            get_music_collection().add_playlist(curr_playlist);
                            std::cout << "*****************************************" << std::endl;
                            std::cout << std::endl;
                            std::cout << "Successfully added song in '" << curr_playlist->get_playlist_title() << "' !" << std::endl;
                            std::cout << "There are " << curr_playlist->content_size() << " songs in this playlist" << std::endl;
                            std::cout << std::endl;
                            std::cout << "*****************************************" << std::endl;
                            break;
                        }
                        
                    }
                    if (!success && _playlist != "show collection")
                    {
                        std::cout << "No playlist with this title. Try again! To see playlists type 'show collection'." << std::endl;
                    }
                    else if (_playlist == "show collection")
                    {
                        get_music_collection().print_playlists();
                    }
                    
                }

            }
            
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
