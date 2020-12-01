#ifndef SYSTEM_H_
#define SYSTEM_H_

class System
{
    private:
        
    public:
        static System& i();
        System(const System&) = delete;
        void operator =(const System&) = delete;

        System();
        ~System();

        void run_program();

};

#endif