#ifndef HEBRA_T
#define HEBRA_T

#include<iostream>
#include<thread>
#include<chrono>

typedef std::chrono::duration<int,std::milli> millisec;

const int NUM_PRIORITY{9};

const millisec CPU_TIME(500);

const int MIN_TIME{100}, MAX_TIME{10000};

class Hebra_t{
    private:
        int priority{0};

        int id_process{0};

        millisec time_process{MIN_TIME};

        static int count;

    public:
        Hebra_t();

        void run_process();

        void change_priority(int);

        int get_priority();

        bool has_finished();

        int getID();

        millisec get_time();
};

#endif