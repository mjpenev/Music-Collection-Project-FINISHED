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
    std::cout << "- show collection - Shows a list with information for all songs in collection." << std::endl;
    std::cout << "- help - Shows a list with supported commands." << std::endl;
    std::cout << "- exit - Closing files and exiting program." << std::endl;
    std::cout << std::endl;
    std::cout << "====================   Once you've logged in you can   =====================" << std::endl;
    std::cout << std::endl;
    std::cout << "- add genres - Adds genres to User's favourites." << std::endl;
    std::cout << "- remove genre - Removes a genre from User's favourites. " << std::endl;
    std::cout << "- show playlist - Shows information for all songs in a playlist. " << std::endl;
    std::cout << "- generate playlist -  Generates new playlist by criteria. "<<std::endl;
    std::cout << "- add song -  Adds a song in mucis collection. "<<std::endl;
    std::cout << "- rate song - Allows user to set rating. (User can rate a song once)" << std::endl;
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

void System::set_info(std::string _content)
{
    this->to_write = _content;
}
void System::set_path(std::string _path)
{
    this->file_path = _path;
}
void System::write_in_string(std::string _to_write)
{
    this->to_write += _to_write;
}
std::string &System::get_info()
{
    return this->to_write;
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
void System::_updateFile(std::string _path)
{
    std::ofstream writeInFile(_path);
    writeInFile << to_write;
    writeInFile << "*" << std::endl;
}
void System::read_users(Register &users)
{
    std::istringstream lineIn(file_info);
    std::vector<std::string> words_user;
    std::string word;
    while(lineIn >> word)
    {
        words_user.push_back(word);
    }
    for (int i = 0; i < words_user.size(); i++)
    {
        if (words_user[i] == "User:")
        {
            int counter = 1;
            User* curr = new User;
            curr->set_username(words_user[i + 1]);
            while (words_user[i + counter] != "|")
            {
                if (words_user[i + counter] == "Password:")
                {
                    curr->set_password(words_user[i  + counter + 1]);
                }
                else if (words_user[i + counter] == "name:")
                {
                    std::string fn = words_user[i  + counter + 1] + ' ' + words_user[i  + counter + 2] + ' ' + words_user[i  + counter + 3];
                    curr->set_full_name(fn);
                }
                else if (words_user[i + counter] == "birth:")
                {
                    Date result;
                    std::string _date = words_user[i  + counter + 1];
                    for (int i = 0; i < _date.length(); i++)
                    {
                        if (_date[i] == '-')
                        {
                            _date[i] = ' ';
                        }
                        
                    }
                    std::vector <int> nums;
                    int num;
                    std::istringstream lineOfNums(_date);
                    while(lineOfNums >> num)
                    {
                        nums.push_back(num);
                    }
                    Date d;
                    if (d.isValid(nums[2], nums[1], nums[0]))
                    {
                        result.setDay(nums[2]);
                        result.setMonth(nums[1]);
                        result.setYear(nums[0]);
                    }
                    nums.clear();
                    curr->set_birth_date(result);
                }
                else if (words_user[i + counter] == "genres:")
                {
                    int k = 1;
                    while(words_user[i + counter + k] != "|" )
                    {
                        curr->add_fav_genre(words_user[i + counter + k]);
                        k++;
                    }
                    std::pair<User*, std::set<Playlist*>> curr_pair;
                    curr_pair.first = curr;
                    std::set<Playlist*> playlists;
                    curr_pair.second = playlists;
                    users.get_allUsers().insert(curr_pair);
                }
                counter++;
            }
        }
        
    }
}
void System::read_songs(Collection &songs)
{
    std::vector<std::string> helper;
    std::string elem;
    std::istringstream myStream(file_info);
    while(myStream >> elem)
    {
        helper.push_back(elem);
    }
    for (int i = 0; i < helper.size(); i++)
    {
        if (helper[i] == "Song:")
        {
            Song* curr = new Song;
            int p = 1;
            std::string _title;
            while (helper[i + p] != "By:")
            {
                _title += helper[i + p];
                _title += ' ';
                p++; 
            }
            curr->set_title(_title);
            int counter = 1;
            while (helper[i + counter] != "|")
            {
                if (helper[i + counter] == "By:")
                {
                    int k = 0;
                    std::string _artist;
                    while (helper[i + counter + k + 1] != "Genre:")
                    {
                        _artist += helper[i + counter + k + 1];
                        _artist += ' ';
                        k++;
                    }
                    curr->set_artist(_artist);
                }
                else if (helper[i + counter] == "Genre:")
                {
                    int k = 0;
                    std::string _genre;
                    while (helper[i + counter + k + 1] != "Album:")
                    {
                        _genre += helper[i + counter + k + 1];
                        _genre += ' ';
                        k++;
                    }
                    curr->set_genre(_genre);
                }
                else if (helper[i + counter] == "Album:")
                {
                    int k = 0;
                    std::string _album;
                    while (helper[i + counter + k + 1] != "Year")
                    {
                        _album += helper[i + counter + k + 1];
                        _album += ' ';
                        k++;
                    }
                    curr->set_album(_album);
                }
                else if (helper[i + counter] == "release:")
                {
                    std::string _year;
                    _year = helper[i  + counter + 1];
                    int y = 0;
                    std::istringstream turnToInt(_year);
                    turnToInt >> y;
                    curr->set_year(y);
                }
                else if (helper[i + counter] == "Rating:")
                {
                    int rate_num = 0;
                    std::string _rating;
                    std::istringstream turnToNum(_rating);
                    turnToNum >> rate_num;
                    curr->set_rating(rate_num);
                }
                counter++;
            }
            songs.add_song(curr);

        }

    }
    
}
void System::run_program()
{
    std::string command;
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
    std::cout << std::endl;
    set_path("C:\\Users\\User\\desktop\\test.txt");
    this->file.open(get_path(), std::ios::in);
    getline(this->file, this->file_info, '*');
    write_in_string(get_file_info());
    read_songs(get_music_collection());
    read_users(get_content());
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
                std::cin.ignore();
                std::string new_command; 
                while (new_command != "sign out")
                {
                    if (!checkUser)
                    {
                        break;
                    }
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
                            if (it->first->get_username() == _username)
                            {
                                break;
                            }
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
                                         
                            std::cout << "Genre successfully added to favourites!" << std::endl;
                        }

                    }
                    else if (new_command == "remove genre")
                    {
                        std::string genre_to_remove;
                        auto it = get_content().get_allUsers().begin();
                        for (; it != get_content().get_allUsers().end(); it++)
                        {
                            if (it->first->get_username() == _username)
                            {
                                break;
                            }

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
                        std::string file_insertion = "Song: " + _title + " By: " + _artist + " Genre: " + _genre + 
                        " Album: " + _album + " Year of release: " + std::to_string(_year) + " Rating: " + std::to_string(curr->get_rating()) + " Raters: "
                        + std::to_string(curr->get_people()) + "(" + std::to_string(curr->get_helper()) + ") |" + '\n';
                        write_in_string(file_insertion);
                        std::ofstream updateSong(this->file_path);
                        updateSong << to_write;
                        std::cout << "************************************************************************************************" <<std::endl;
                        std::cout << std::endl;
                        std::cout << "You're song is ready! Successfully added to music collection! To see all songs type (show collection)." << std::endl;
                        std::cout << std::endl;
                        std::cout << "************************************************************************************************" <<std::endl;

                    }
                    else if (new_command == "generate playlist")
                    {
                        
                    }
                    else if (new_command == "show playlist")
                    {
                        
                    }
                    else if (new_command == "show collection")
                    {
                        if (this->music_collection.get_songs().empty())
                        {
                            std::cout << "Music collection is currently empty! You can add some songs by the 'add song' command." << std::endl;
                        }
                        else
                        {
                            std::cout << "*************************************" << std::endl;
                            std::cout << std::endl;
                            std::cout << "     All songs in collection : " << this->music_collection.get_songs().size() << std::endl;
                            std::cout << std::endl;
                            std::cout << "*************************************" << std::endl;
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
            write_in_string(user_insertion);
            _updateFile(get_path());   
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
    file.close();
    std::cout << "Closing files. Exiting program..." << std::endl;
}
