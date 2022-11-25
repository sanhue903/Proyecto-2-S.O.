#include "Runqueue.h"

void Runqueue::add_process(Hebra_t process){
    int priority{process.get_priority()};

    std::lock_guard<std::mutex> mt(this->mutex_runqueue);

    this->queue.push(process);
}

Hebra_t Runqueue::pop_process(){
    std::lock_guard<std::mutex> mt(this->mutex_runqueue);

    Hebra_t process{this->queue.top()};
    this->queue.pop();


    return process;
}

bool Runqueue::is_empty(){
    std::lock_guard<std::mutex> mt(this->mutex_runqueue);
    return queue.empty();
}
