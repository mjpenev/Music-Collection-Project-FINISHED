#include <iostream>
#include "FunctionCaller.h"

void Functions::add_genre(std::string _username, Register &users, std::string &path_, std::string &file_info)
{
    auto it = users.get_allUsers().begin();
    for (; it != users.get_allUsers().end(); it++)
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
        int position = file_info.find(helper_str);    
        position += helper_str.length();    
        file_info.insert(position + 1, genre_to_add + " ");
        std::ofstream updateGenre(path_);
        updateGenre << file_info;
        updateGenre << " " << std::endl;
        std::cout << "Genre successfully added to favourites!" << std::endl;
    }
}
void Functions::remove_genre(std::string _username, Register &users, std::string &path_, std::string &file_info)
{
    std::string genre_to_remove;
    auto it = users.get_allUsers().begin();
    for (; it != users.get_allUsers().end(); it++)
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
                int position = file_info.find(remove_after);
                position += remove_after.length();
                int new_position = position;
                std::string _genres;
                while (file_info[position] != '|')
                {
                    _genres += file_info[position];
                    position++;
                }
                new_position += _genres.find(genre_to_remove);
                file_info.erase(new_position, genre_to_remove.length() + 1); // + 1 cause of the spacebar at the end
                std::ofstream saveInfo(path_);
                saveInfo << file_info;
            }
        }
        if (!success)
        {
            std::cout << "No genre '" << genre_to_remove << "' in favourites!" << std::endl;
        }
    }
}
void Functions::add_song(std::string &file_info, Printer &printer_, Collection &songs, std::string &path_)
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
    songs.add_song(curr);
    std::string rate_str = std::to_string(curr->get_rating());
    rate_str.resize(3);
    std::string file_insertion = "Song: " + _title + " By: " + _artist + " Genre: " + _genre + 
    " Album: " + _album + " Year of release: " + std::to_string(_year) + " Rating: " + rate_str + " Raters: "
    + std::to_string(curr->get_people()) + " (" + std::to_string(curr->get_helper()) + ") |" + '\n';
    std::ofstream updateSong(path_);
    file_info += file_insertion;
    updateSong << file_info;
    printer_.print_ready_song();
}
void Functions::show_playlist(std::string _username, Register &users)
{
    std::string to_search;
    std::cout << "Which playlist do you want to explore: ";
    getline(std::cin, to_search);
    auto it = users.get_allUsers().begin();
    for ( ; it != users.get_allUsers().end(); it++)
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
void Functions::rate_song(std::string _username, std::string &path_, std::string &file_info, Collection &songs)
{
    if (songs.get_songs().empty())
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
        auto it = songs.get_songs().begin();
        for (; it != songs.get_songs().end(); it++)
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
                int position = file_info.find(curr->get_title());
                int const_size = file_info.length();
                int new_position = position;
                for (int i = position; i < const_size; i++)
                {
                    if (file_info[i] == '.') break;
                    new_position++;
                } 
                std::string rate_str = std::to_string(num_to_set);
                rate_str.resize(4); // rating with only 2 digits after dot
                file_info.erase(new_position - 1, 3); // - 1 cause the number before dot must be deleted // 3 cause of the symbols after dot
                file_info.insert(new_position - 1, rate_str);
                
                std::ofstream updateRating(path_);
                updateRating << file_info;
            }
        }
    }
}
void Functions::sign_up(Register &users, std::string &path_, std::string &file_info)
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
        if (!(users.get_allUsers().empty()))
        {
            for (auto it = users.get_allUsers().begin(); it != users.get_allUsers().end(); it++)
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
    users.insert_in_system(current);
    std::cout << "Registration is succesfully made! Type 'sign in' to log into your account!" << std::endl; 
    std::string user_insertion = "User: " + _username + " Password: " + _password + 
    " Full name: " + _fullname + " Date of birth: " + std::to_string(y) + "-" + std::to_string(m) + "-" + std::to_string(d) + '\n'
    + _username + "'s favourite genres: |" + '\n';
    file_info += user_insertion;
    std::ofstream updateUser(path_);
    updateUser << file_info;
}
void Functions::show_collection(Collection &songs, Printer &printer_)
{
    if (songs.get_songs().empty())
    {
        std::cout << "Music collection is currently empty! You can add some songs by the 'add song' command." << std::endl;
    }
    else
    {
        printer_.print_collection_start(songs.get_songs().size());
        songs.print_songs();
    }
}
void Functions::show_users(Register &users)
{
    if (users.get_allUsers().empty())
    {
        std::cout << "No registered users yet!" << std::endl;
    }
    users.print_all_Users();  
}