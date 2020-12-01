#ifndef DATE_H_
#define DATE_H_

class Date
{
    private:
        int day;
        int month;
        int year;
        void copyDate(Date &other);

    public:
        bool isValid(int day, int month, int year);
        void setDay(int _day);
        void setMonth(int _month);
        void setYear(int _year);
        int getDay();
        int getMonth();
        int getYear();
        bool checkIfLeap(int _year);
        void printDate();

        Date() : day(0), month(0), year(0) {}
        Date(Date &other);
        Date& operator =(Date &other);
        bool operator < (Date other);
        bool operator > (Date other);
        bool operator <= (Date &other);
        bool operator >= (Date &other);
        ~Date();



};


#endif