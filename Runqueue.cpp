#include "Runqueue.h"

Runqueue::Runqueue() {
    swapped = false;
}

void Runqueue::add_process(Hebra_t* process){
    if (!swapped) {
        active.push(process);
    } else {
        expired.push(process);
    }
}

void Runqueue::add_expired(Hebra_t* process) {
    if (!swapped) {
        expired.push(process);
    } else {
        active.push(process);
    }
}

Hebra_t* Runqueue::pop_process(){
    Hebra_t* process;
    if (!swapped) {
        process = this->active.top();
        this->active.pop();
    } else {
        process = this->expired.top();
        this->expired.pop();
    }
    return process;
}

bool Runqueue::is_empty(){
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