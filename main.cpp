#include "Runqueue.h"

#define N 10    // Numero de hebras creadas inicialmente
#define M 4     // Numero de CPUs

std::mutex mtx;
std::condition_variable cond;

void process_scheduler(Runqueue&);
void process_creator(Runqueue&);

int main() {
    srand(time(NULL));

    Runqueue rq;

    std::vector<std::thread> hebras_e;

    for (size_t i = 0; i < M; i++)
        hebras_e.emplace_back(std::thread(process_scheduler, std::ref(rq)));

    std::thread creator_thread(process_creator, std::ref(rq));

    for (size_t i = 0; i < M; i++)
        hebras_e[i].join(); 
    
    return 0;
}

void process_scheduler(Runqueue& rq) {
    while (true) {
        std::unique_lock<std::mutex> locker(mtx);
        if (!rq.is_empty()) {
            Hebra_t aux = rq.pop_process();
            locker.unlock();

            aux.run_process();
            
            locker.lock();
            if (!aux.has_finished()) {
                if (aux.get_priority() < NUM_PRIORITY) {
                    aux.change_priority(aux.get_priority() + 1); 
                }
                rq.add_expired(aux);
            }
            locker.unlock();
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
void process_creator(Runqueue& rq) {
    while (true) {
        std::unique_lock<std::mutex> locker(mtx);
        cond.wait(locker);

        Hebra_t procesos[N];

        for (auto i : procesos)
            rq.add_process(i); 

        locker.unlock();
    }
}
