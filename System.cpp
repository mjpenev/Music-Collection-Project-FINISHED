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
                        auto it = get_content().get_allUsers().begin();
                        for (; it != get_content().get_allUsers().end(); it++)
                        {
                            if (it->first->get_username() == _username) break;
                        }
                        std::cout << "Add this genre to favourite: ";
                        std::string genre_to_add;
                        getline(std::cin, genre_to_add);
                        bool success = true;
                        int const_size = it->first->get_genres().size();
                        for(int i = 0; i < const_size; i++)
                        {
                            it->first->get_genres().push(it->first->get_genres().front());
                            if (it->first->get_genres().front() == genre_to_add)
                            {
                                success = false;
                                it->first->get_genres().pop();
                                break;
                            }
                            it->first->get_genres().pop();
                        }
                        if (!success)
                        {
                            std::cout << "Genre is already added in favourites!" << std::endl;
                        }
                        else
                        {
                            it->first->add_fav_genre(genre_to_add);   
                            std::string helper_str;
                            helper_str = it->first->get_username() +  "'s favourite genres:";
                            int position = get_file_info().find(helper_str);    
                            position += helper_str.length();    
                            get_file_info().insert(position + 1, genre_to_add + " ");
                            std::ofstream updateGenre(get_path());
                            updateGenre << get_file_info();
                            updateGenre << " " << std::endl;
                            set_file_end();
                            std::cout << "Genre successfully added to favourites!" << std::endl;
                        }
                    }
                    else if (new_command == "remove genre")
                    {
                        std::string genre_to_remove;
                        auto it = get_content().get_allUsers().begin();
                        for (; it != get_content().get_allUsers().end(); it++)
                        {
                            if (it->first->get_username() == _username) break;
                        }
                        if (it->first->get_genres().empty())
                        {
                            std::cout << "This user doesn't have favourite genres yet!" << std::endl;
                        }
                        else
                        {
                            bool success = false;
                            std::cout << "Select genre to remove: ";
                            getline(std::cin, genre_to_remove);
                            for (int i = 0; i < it->first->get_genres().size(); i++)
                            {
                                it->first->get_genres().push(it->first->get_genres().front());
                                it->first->get_genres().pop();
                                if (it->first->get_genres().front() == genre_to_remove)
                                {
                                    it->first->get_genres().pop();
                                    success = true;
                                    std::cout << "Genre removed from favourites!" << std::endl;
                                    std::string remove_after = it->first->get_username() + "'s favourite genres: ";
                                    int position = get_file_info().find(remove_after);
                                    position += remove_after.length();
                                    int new_position = position;
                                    std::string _genres;
                                    while (get_file_info()[position] != '|')
                                    {
                                        _genres += get_file_info()[position];
                                        position++;
                                    }
                                    new_position += _genres.find(genre_to_remove);
                                    get_file_info().erase(new_position, genre_to_remove.length() + 1); // + 1 cause of the spacebar at the end
                                    std::ofstream saveInfo(this->file_path);
                                    saveInfo << get_file_info();
                                    set_file_end();
                                }
                            }
                            if (!success)
                            {
                                std::cout << "No genre '" << genre_to_remove << "' in favourites!" << std::endl;
                            }
                        }
                    }
                    else if(new_command == "add song")
                    {
                        Song *curr = new Song;
                        std::string _album, _artist, _genre, _rating, _title, _playlist;
                        int _year;
                        std::cout << "Title of the song: ";
                        getline(std::cin, _title);
                        curr->set_title(_title);
                        std::cout << "Name the artist: ";
                        getline(std::cin, _artist);
                        curr->set_artist(_artist);
                        std::cout << "Album (not necessary) : ";
                        getline(std::cin, _album);
                        curr->set_album(_album);
                        std::cout << "Genre of song: ";
                        getline(std::cin, _genre);
                        curr->set_genre(_genre);
                        curr->set_helper(0);
                        curr->set_people(0);
                        do
                        {
                            std::cout << "Year of release: ";
                            std::cin >> _year;
                        } while (_year < 0 || _year > 2020);
                        std::cin.ignore();
                        curr->set_year(_year);
                        this->music_collection.add_song(curr);
                        std::string rate_str = std::to_string(curr->get_rating());
                        rate_str.resize(3);
                        std::string file_insertion = "Song: " + _title + " By: " + _artist + " Genre: " + _genre + 
                        " Album: " + _album + " Year of release: " + std::to_string(_year) + " Rating: " + rate_str + " Raters: "
                        + std::to_string(curr->get_people()) + " (" + std::to_string(curr->get_helper()) + ") |" + '\n';
                        std::ofstream updateSong(file_path);
                        get_file_info() += file_insertion;
                        updateSong << get_file_info();
                        set_file_end();
                        this->printer.print_ready_song();

                    }
                    else if (new_command == "generate playlist")
                    {
                        this->generator.generate_playlist(_username, this->get_music_collection(), this->get_content(), this->get_printer());
                    }
                    else if (new_command == "show playlist")
                    {
                        std::string to_search;
                        std::cout << "Which playlist do you want to explore: ";
                        getline(std::cin, to_search);
                        auto it = this->get_content().get_allUsers().begin();
                        for ( ; it != this->get_content().get_allUsers().end(); it++)
                        {
                            if (it->first->get_username() == _username) break;
                        }
                        auto iter = it->second.begin();
                        Playlist *curr;
                        bool success = false;
                        for ( ; iter != it->second.end(); iter++)
                        {
                            curr = *iter;
                            if (curr->get_playlist_title() == to_search)
                            {
                                success = true;
                            }
                        }
                        if (!success)
                        {
                            std::cout << "There is no playlist with this title!" << std::endl;
                        }
                        else
                        {
                            curr->print_content();
                        } 
                    }
                    else if (new_command == "show collection")
                    {
                        if (this->music_collection.get_songs().empty())
                        {
                            std::cout << "Music collection is currently empty! You can add some songs by the 'add song' command." << std::endl;
                        }
                        else
                        {
                            this->printer.print_collection_start(this->music_collection.get_songs().size());
                            this->music_collection.print_songs();
                        }
                    }
                    else if(new_command == "show users")
                    {
                        if (this->get_content().get_allUsers().empty())
                        {
                            std::cout << "No registered users yet!" << std::endl;
                        }
                        get_content().print_all_Users();   
                    }
                    else if(new_command == "rate song")
                    {
                        if (this->music_collection.get_songs().empty())
                        {
                            std::cout << "Music collection is empty." << std::endl;
                        }
                        else
                        {
                            int rating;
                            std::string song_to_rate;
                            std::cout << "Which song do you want to rate?" << std::endl;
                            getline(std::cin, song_to_rate);
                            bool success = false;
                            Song *curr;
                            auto it = this->music_collection.get_songs().begin();
                            for (; it != this->music_collection.get_songs().end(); it++)
                            {
                                curr = *it;
                                if (curr->get_title() == song_to_rate)
                                {
                                    success = true;
                                    break;
                                }
                            }
                            if (!success)
                            {
                                std::cout << "Invalid song title! Please, try again." << std::endl;
                            }
                            else
                            {
                                bool rated = false;
                                for (int i = 0; i < curr->get_names().size(); i++)
                                {
                                    if (curr->get_names()[i] == _username)
                                    {
                                        rated = true;
                                        break;
                                    }
                                }
                                if (rated)
                                {
                                    std::cout << "You've already rated! You can rate only once for a song." << std::endl;
                                }
                                else
                                {
                                    do
                                    {
                                        std::cout << "Your rate (from 1 to 10) for this song is : ";
                                        std::cin >> rating;
                                        if (rating < 0 || rating > 10)
                                        {
                                            std::cout << "Invalid rating! Try again." << std::endl;
                                        }
                                    } while (rating < 0 || rating > 10);
                                    int new_people = curr->get_people() + 1;
                                    curr->set_people(new_people);
                                    curr->set_helper(curr->get_helper() + rating);
                                    double num_to_set = (curr->get_helper()) / (double)(curr->get_people());
                                    curr->set_rating(num_to_set);
                                    curr->push_person(_username);
                                    std::cout << "You successfully rated this song! Thank you!" << std::endl;
                                    std::cin.ignore();
                                    int position = get_file_info().find(curr->get_title());
                                    int const_size = get_file_info().length();
                                    int new_position = position;
                                    for (int i = position; i < const_size; i++)
                                    {
                                        if (get_file_info()[i] == '.') break;
                                        new_position++;
                                    } 
                                    std::string rate_str = std::to_string(num_to_set);
                                    rate_str.resize(4); // rating with only 2 digits after dot
                                    get_file_info().erase(new_position - 1, 3); // - 1 cause the number before dot must be deleted // 3 cause of the symbols after dot
                                    get_file_info().insert(new_position - 1, rate_str);
                                    
                                    std::ofstream updateRating(file_path);
                                    updateRating << get_file_info();
                                    set_file_end();
                                }
                            }
                        }
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
            std::cin.ignore();
            curr->set_birth_date(*(bd));

            std::pair<User*, std::set<Playlist*>> current;
            current.first = curr;
            std::set<Playlist*> songs;
            current.second = songs;
            get_content().insert_in_system(current);
            std::cout << "Registration is succesfully made! Type 'sign in' to log into your account!" << std::endl; 
            std::string user_insertion = "User: " + _username + " Password: " + _password + 
            " Full name: " + _fullname + " Date of birth: " + std::to_string(y) + "-" + std::to_string(m) + "-" + std::to_string(d) + '\n'
            + _username + "'s favourite genres: |" + '\n';
            get_file_info() += user_insertion;
            std::ofstream updateUser(file_path);
            updateUser << get_file_info();
            set_file_end();
        }
        else if(checkWord(0) == "show" && checkWord(1) == "collection")
        {
            get_music_collection().print_songs();
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
