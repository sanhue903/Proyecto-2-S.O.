#include "Runqueue.h"
#include <cstdlib>

std::mutex mtx;
std::condition_variable cond;

void process_scheduler(Runqueue&);
void process_creator(Runqueue&, int);

int main(int argc, char **argv) {
    srand(time(NULL));

    Runqueue rq;

    std::vector<std::thread> hebras_e;

    int M{(int)std::strtol(argv[1], nullptr, 0)}; // Numero de CPUs (Hebras Scheduler)
    int N{(int)std::strtol(argv[2], nullptr, 0)}; // Numero de hebras creadas en cada ola de la hebra creadora de procesos

    std::thread creator_thread(process_creator, std::ref(rq), N);
    
    for (size_t i = 0; i < M; i++)
        hebras_e.emplace_back(std::thread(process_scheduler, std::ref(rq)));
    
    for (size_t i = 0; i < M; i++)
        hebras_e[i].join(); 

    creator_thread.join();
    
    return 0;
}

void process_scheduler(Runqueue& rq) {
    while (true) {
        std::unique_lock<std::mutex> locker(mtx);
        if (!rq.is_empty()) {
            Hebra_t* aux = rq.pop_process();
            locker.unlock();

            aux->run_process();
            
            if (!aux->has_finished()) {
                aux->change_priority(); 
                
                locker.lock();
                
                rq.add_expired(aux);

                locker.unlock();
            } else {
                delete aux;
            }
                
        } else if (!rq.is_expired_empty()) {
            rq.swap();
            locker.unlock();
        } else {
            /*
                Si se acaban las hebras, se imprime un mensaje y se manda una 
                señal a la hebra creadora de procesos para que cree mas procesos
                y los agregue a la cola activa.
            */
            locker.unlock();
            std::cout << std::this_thread::get_id() << ") No processes left, waiting for more...\n";
            cond.notify_one();  
        }
    }
}

/*  
    Rutina que espera concurrentemente a una señal de que las runqueues estan vacias
    para crear nuevos procesos y agregarlas.
*/
void process_creator(Runqueue& rq, int N) {
    while (true) {
        std::unique_lock<std::mutex> locker(mtx);
        cond.wait(locker);

        for (int i = 0; i < N; i++)
            rq.add_process(new Hebra_t); 

        locker.unlock();
    }
}

