#include "Runqueue.h"

void process_scheduler(Runqueue&,Runqueue&);

int nivel = 0;

int main(){
    srand(time(NULL));

    Runqueue activa, expirada;
    std::thread E(process_scheduler, activa, expirada);
    return 0;
}

void process_scheduler(Runqueue& activa, Runqueue& expirada){
    while(true){
        while(!activa.is_empty()){
            
        }

        while(!expirada.is_empty()){
            
        }
    }

}