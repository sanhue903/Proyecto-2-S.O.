#ifndef RUNQUEUE
#define RUNQUEUE

#include "Hebra_t.h"
#include <queue>
#include <vector>
#include <unistd.h>
#include <mutex>


struct Compare {
    bool operator()(Hebra_t& p1, Hebra_t& p2) {
        return p1.get_priority() > p2.get_priority();
    }
};

class Runqueue{
private:
    bool swapped;
    std::priority_queue<Hebra_t, std::vector<Hebra_t>, Compare> active;
    std::priority_queue<Hebra_t, std::vector<Hebra_t>, Compare> expired;

    std::mutex mutex_runqueue;

public:
    Runqueue();

    void add_process(Hebra_t);

    void add_expired(Hebra_t);

    Hebra_t pop_process();

    bool is_empty();

    bool is_expired_empty();

    int getSize();

    void swap();
};

#endif