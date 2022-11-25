#include "Hebra_t.h"

int Hebra_t::count{0};

Hebra_t::Hebra_t(){
    int new_time{(rand() + MIN_TIME) % MAX_TIME};
    this->time_process = millisec(new_time);
    this->priority = rand() % (NUM_PRIORITY); 

    this->id_process = count++;
}


void Hebra_t::run_process(){
    millisec aux{this->time_process < CPU_TIME ? this->time_process : CPU_TIME};

    std::this_thread::sleep_for(aux);

    std::cout << "Process: " << this->id_process << "-" << this->priority << " time: " << aux.count() << "ms" << std::endl;

    this->time_process = this->time_process - CPU_TIME;
}


void Hebra_t::change_priority(int new_priority){
    this->priority = new_priority;
}


int Hebra_t::get_priority(){
    return this->priority;
}


bool Hebra_t::has_finished(){
    return this->time_process.count() <= 0;
}