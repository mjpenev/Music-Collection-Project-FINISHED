#ifndef REGISTER_H_
#define REGISTER_H_

#include <vector>
#include <string>
#include "User.h"

class Register
{
    private:
        std::vector<User> allUsers;
    public:
        void addUser(User _user);
        
};

#endif