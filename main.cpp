#include "Runqueue.h"

const int N = 10;
const int M = 4;

void process_scheduler(Runqueue&);

int main(){
    srand(time(NULL));

    Runqueue rq;

    Hebra_t procesos[N];

    for (auto i : procesos)
        rq.add_process(i); 

    std::vector<std::thread> hebras_e;

    for (size_t i = 0; i < M; i++)
        hebras_e.emplace_back(std::thread(process_scheduler, std::ref(rq)));

    for (size_t i = 0; i < M; i++)
        hebras_e[i].join(); 
    
    return 0;
}

void process_scheduler(Runqueue& rq) {
    while (true) {

        if (!rq.is_empty()) {
            Hebra_t aux = rq.pop_process();

            aux.run_process();

            if (!aux.has_finished()) {
                if (aux.get_priority() < NUM_PRIORITY) {
                    aux.change_priority(aux.get_priority() + 1); 
                }
                rq.add_expired(aux);
            }
        } else if (!rq.is_expired_empty()) {
            rq.swap();
        } else {
            std::cout << "No processes left, waiting for more...\n";
            sleep(1);
        }
    }
}

