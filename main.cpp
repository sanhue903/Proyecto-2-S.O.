#include "Runqueue.h"


void process_scheduler(Runqueue&, Runqueue&);

int N = 10;
int M = 4;


int main(){
    srand(time(NULL));

    Runqueue activa, expirada;

    Hebra_t procesos[N];

    for (auto i : procesos)
        activa.add_process(i); 

    std::vector<std::thread> hebras_e;

    for (size_t i = 0; i < M; i++)
        hebras_e.emplace_back(std::thread(process_scheduler, std::ref(activa), std::ref(expirada)));

    for (size_t i = 0; i < M; i++)
        hebras_e[i].join(); 
    
    return 0;
}

void process_scheduler(Runqueue& activa, Runqueue& expirada){
    while(true){

        activa.mutex_runqueue.lock;

        while(!activa.is_empty()){
            Hebra_t aux{activa.pop_process()};

            activa.mutex_runqueue.unlock();

            aux.run_process();

            if (!aux.has_finished()){
                if (aux.get_priority() < NUM_PRIORITY)
                    aux.change_priority(aux.get_priority() + 1); 

                expirada.mutex_runqueue.lock();

                expirada.add_process(aux);
            }

            
        }

        if (activa.)
        activa.mutex_runqueue.unlock();

        expirada.mutex_runqueue.lock();
        while(!expirada.is_empty()){
            activa.add_process(expirada.pop_process());
        }
    }

}
/*
void process_scheduler(Runqueue& activa, Runqueue& expirada){
    while(true){
        while(!activa.is_empty()){
            Hebra_t aux{activa.pop_process()};

            aux.run_process();

            if (!aux.has_finished()){
                if (aux.get_priority() < NUM_PRIORITY)
                    aux.change_priority(aux.get_priority() + 1); 

                expirada.add_process(aux);
            }
        }

        while(!expirada.is_empty()){
            activa.add_process(expirada.pop_process());
        }
    }

}*/