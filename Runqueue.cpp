#include "Runqueue.h"

Runqueue::Runqueue() {
    swapped = false;
}

void Runqueue::add_process(Hebra_t process){
    int priority = process.get_priority();

    //std::lock_guard<std::mutex> mt(this->mutex_runqueue);

    if (!swapped) {
        active.push(process);
    } else {
        expired.push(process);
    }
}

void Runqueue::add_expired(Hebra_t process) {
    if (!swapped) {
        expired.push(process);
    } else {
        active.push(process);
    }
}

Hebra_t Runqueue::pop_process(){
    //std::lock_guard<std::mutex> mt(this->mutex_runqueue);
    Hebra_t process;
    if (!swapped) {
        process = this->active.top();
        //std::cout << "popeando " << process.getID() << "-" << process.get_priority() << " tiempo:"<< process.get_time().count() << "ms" << "\n";
        this->active.pop();
    } else {
        process = this->expired.top();
        //std::cout << "popeando " << process.getID() << "-" << process.get_priority() << " tiempo:"<< process.get_time().count() << "ms" << "\n";
        this->expired.pop();
    }
    return process;
}

bool Runqueue::is_empty(){
    //std::lock_guard<std::mutex> mt(this->mutex_runqueue);
    return !swapped ? active.empty() : expired.empty();
}

bool Runqueue::is_expired_empty() {
    return !swapped ? expired.empty() : active.empty();
}

int Runqueue::getSize() {
    return !swapped ? active.size() : expired.size();
}

void Runqueue::swap() {
    swapped = !swapped;
}