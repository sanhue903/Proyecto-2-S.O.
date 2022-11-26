#ifndef RUNQUEUE
#define RUNQUEUE

#include "Hebra_t.h"
#include <queue>
#include <vector>
#include <mutex>


struct Compare {
    bool operator()(Hebra_t& p1, Hebra_t& p2) {
        return p1.get_priority() > p2.get_priority();
    }
};

class Runqueue{
    private:
        std::priority_queue<Hebra_t, std::vector<Hebra_t>, Compare> queue;

        std::mutex mutex_runqueue;
    
    public:
        void add_process(Hebra_t);

        Hebra_t pop_process();

        bool is_empty();
};

#endif