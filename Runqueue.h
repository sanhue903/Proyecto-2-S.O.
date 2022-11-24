#ifndef RUNQUEUE
#define RUNQUEUE

#include "Hebra_t.h"
#include <queue>
#include <vector>
#include <mutex>

const int NUM_PRIORITY{10};

class Runqueue{
    private:
        std::vector<std::queue<Hebra_t>> priority_queue;

        std::mutex mutex_runqueue;

        int size{0};

        int in_priority{0};
    
    public:
        Runqueue();

        void add_process(Hebra_t);

        Hebra_t pop_process();

        bool is_empty();
};

#endif