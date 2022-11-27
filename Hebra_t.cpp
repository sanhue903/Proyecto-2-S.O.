#include "Hebra_t.h"

int Hebra_t::count{0};

Hebra_t::Hebra_t(){
    int new_time{(rand() + MIN_TIME) % MAX_TIME};
    this->time_process = millisec(new_time);

    this->change_priority(); 

    this->id_process = count++;
}


void Hebra_t::run_process(){
    millisec aux{this->time_process < CPU_TIME ? this->time_process : CPU_TIME};

    std::this_thread::sleep_for(aux);

    std::cout << "Process: " << this->id_process << "-" << this->priority << " time: " << aux.count() << "ms" << std::endl;

    this->time_process = this->time_process - CPU_TIME;
}


void Hebra_t::change_priority(){
    int new_priority{this->time_process.count() / CPU_TIME.count()};
    
    this->priority = new_priority < NUM_PRIORITY ? new_priority : NUM_PRIORITY;
}


int Hebra_t::get_priority(){
    return this->priority;
}


bool Hebra_t::has_finished() {
    if (this->time_process.count() <= 0) {
        std::cout << "Finished running process " << id_process << "\n";
        return true;
    }
    return false; 
}

int Hebra_t::getID(){
    return id_process;
}

millisec Hebra_t::get_time(){
    return time_process;
}