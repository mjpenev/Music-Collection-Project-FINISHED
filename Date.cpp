#include "Date.h"
#include <iostream>

void Date::copyDate(Date &other)
{
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
}

bool Date::checkIfLeap(int _year)
{
    if (_year % 4 == 0)
    {
        if (_year % 100 == 0) 
        {
            if (_year % 400 == 0) 
            {
                return true;
            }
        }

    } 
    return false;
}


bool Date::isValid(int day, int month, int year)
{
    if (day > 31 || day < 1 || month > 12 || month < 1 || year < 0 || year > 2100)
    {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        return false;
    }
    if (month == 2 && !checkIfLeap(year) && day > 28)
    {
        return false;
    }
    if (checkIfLeap(year) && month == 2 && day > 29)
    {
        return false;
    }

    return true;
    
}


void Date::setDay(int _day)
{
    day = _day;
}

void Date::setMonth(int _month)
{
    month = _month;
}

void Date::setYear(int _year)
{
    year = _year;
}

int Date::getDay()
{
    return day;
}

int Date::getMonth()
{
    return month;   
}

int Date::getYear()
{
    return year;
}

void Date::printDate()
{
    std::cout << day << "-" << month << "-" << year << std::endl;
}

Date::Date(Date &other)
{
    copyDate(other);
}

Date& Date::operator =(Date &other)
{
    if (this != &other)
    {
        copyDate(other);
    }
    return *this;
    
}

bool Date::operator < (Date other)
{
    if (this->year < other.year)
    {
        return true;
    }
    else if (this->year == other.year && this->month < other.month)
    {
        return true;
    }
    else if (this->year == other.year && this->month == other.month && this->day < other.day)
    {
        return true;
    }

    return false;
}

bool Date::operator > (Date other)
{
    if (this->year > other.year)
    {
        return true;
    }
    else if (this->year == other.year && this->month > other.month)
    {
        return true;
    }
    else if (this->year == other.year && this->month == other.month && this->day > other.day)
    {
        return true;
    }

    return false;
}

bool Date::operator <= (Date &other)
{
    if (this->year < other.year)
    {
        return true;
    }
    else if (this->year == other.year && this->month < other.month)
    {
        return true;
    }
    else if (this->year == other.year && this->month == other.month && this->day <= other.day)
    {
        return true;
    }

    return false;
}
bool Date::operator >= (Date &other)
{
    if (this->year > other.year)
    {
        return true;
    }
    else if (this->year == other.year && this->month > other.month)
    {
        return true;
    }
    else if (this->year == other.year && this->month == other.month && this->day >= other.day)
    {
        return true;
    }

    return false;
}

Date::~Date()
{
    
}
