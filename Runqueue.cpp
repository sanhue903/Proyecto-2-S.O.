#include "Runqueue.h"

Runqueue::Runqueue(){
    for (size_t i = 0; i < NUM_PRIORITY;++i)
        this->priority_queue.push_back(std::queue<Hebra_t>());
}

void Runqueue::add_process(Hebra_t process){
    int priority{process.get_priority()};

    this->mutex_runqueue.lock();

    this->priority_queue[priority].push(process);

    this->size++;

    this->mutex_runqueue.unlock();
}

Hebra_t Runqueue::pop_process(){


    this->mutex_runqueue.lock();

    if (this->priority_queue[in_priority].empty())
        this->in_priority = (this->in_priority + 1)%NUM_PRIORITY;

    Hebra_t process{this->priority_queue[in_priority].front()};
    this->priority_queue[in_priority].pop();

    this->size--;

    this->mutex_runqueue.unlock();

    return process;
}

bool Runqueue::is_empty(){
    if (this->size == 0)
        return true;

    return false;
}
