#include "Runqueue.h"

void Runqueue::add_process(Hebra_t process){
    int priority{process.get_priority()};

    this->queue.push(process);
}

Hebra_t Runqueue::pop_process(){
    Hebra_t process{this->queue.top()};
    std::cout << "popeando " << process.getID() << "-" << process.get_priority() << " tiempo: "<< process.get_time().count() << "ms" << "\n";
    this->queue.pop();

    return process;
}

bool Runqueue::is_empty(){
    return queue.empty();
}
