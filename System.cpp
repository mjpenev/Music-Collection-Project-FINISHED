#include <iostream>
#include "System.h"
#include "User.h"
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

void System::run_program()
{
    Song a, b, c, d;
    Playlist p;
    string command;
    
    while(command != "exit")
    {
        cout << "Insert command: " << endl;
        getline(cin, command);

    }
    a.set_title("Eminem");
    a.set_artist("Lose yourself");
    a.set_album("8 mile");
    a.set_genre("Rap");
    a.set_year(2002);
    a.set_rating(9);
    
    b.set_title("It's my life");
    b.set_artist("Bon Jovi");
    b.set_album("Rock hits");
    b.set_genre("Rock");
    b.set_year(1990);
    b.set_rating(8);
    
    c.set_title("Hear me");
    c.set_artist("Martin Penev");
    c.set_genre("Balada");
    c.set_year(2016);
    c.set_rating(7.5);

    d.set_title("Lubimec 13");
    d.set_artist("Boris Soltariiski");
    d.set_album("Pesnite na Slavi");
    d.set_genre("Chalga");
    d.set_year(2000);
    d.set_rating(10);

    p.add_content(a);
    p.add_content(b);
    p.add_content(c);
    p.add_content(d);

    p.print_content();
}

System::~System()
{
    cout << "Closing files. Exiting program..." << endl;
}
