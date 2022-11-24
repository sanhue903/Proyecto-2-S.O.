#ifndef HEBRA_T
#define HEBRA_T

#include<iostream>
#include<thread>
#include<chrono>

typedef std::chrono::duration<int,std::milli> millisec;

const millisec CPU_TIME(200);
const int MIN_TIME{50}, MAX_TIME{300};

class Hebra_t{
    private:
        int priority{0};

        int id_process{0};

        millisec time_process{MIN_TIME};

    public:
        Hebra_t();

        void run_process();

        void change_priority(int);

        int get_priority();

        int get_id();
};

#endif