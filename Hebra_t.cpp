#include "Hebra_t.h"

Hebra_t::Hebra_t(){
    int new_time{(rand() + MIN_TIME) % MAX_TIME};
    this->time_process = millisec(new_time);

    this->id_process = rand() % 100000;
}

void Hebra_t::run_process(){
    if (time_process < CPU_TIME)
        std::this_thread::sleep_for(time_process);
    else
        std::this_thread::sleep_for(CPU_TIME);

    std::cout << "Process: " << this->id_process << " time: " << this->time_process.count() << "ms" << std::endl;
}

void Hebra_t::change_priority(int new_priority){
    this->priority = new_priority;
}

int Hebra_t::get_priority(){
    return this->priority;
}

int Hebra_t::get_id(){
    return this->id_process;
}