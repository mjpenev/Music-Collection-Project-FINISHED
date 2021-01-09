#include <iostream>
#include "Reader.h"

void Reader::read_users(Register &users, std::string &file_info)
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
void Reader::read_songs(Collection &songs, std::string &file_info)
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
                if (helper[i + p + 1] != "By:")
                {
                    _title += " ";
                }
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