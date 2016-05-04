#include <vector>
#include <queue>
#include <algorithm> // Find o remove if
#include <iostream>
#include "sched_no_mistery.h"
#include "basesched.h"

using namespace std;

//PRIORIDAD 1: 1 quantum
//      - inician acá
//      - cuando se bloquean los pasan a esta prioridad
//PRIORIDAD i: i quantum
//      - una vez que ejecutan i-1 veces se los pasa a esta prioridad

SchedNoMistery::SchedNoMistery(vector<int> argn) {
    //se inicia el quantum default de la Prioridad 1 (1)
    def_quantum.push_back(1);
    //se inicia la cola de ready Prioridad 1
    vq.push_back(std::queue<int>());

    for (n = 1; n < (int)argn.size(); n++) {
        //se inicia su quantum default
        def_quantum.push_back(argn[n]);
        //se inicia su cola de ready
        vq.push_back(queue<int>());
    }
    
    //se inicia el quantum del proceso actual en 0
    quantum = 0;
    return;
}

void SchedNoMistery::load(int pid) {
    //se agrega a la cola de Prioridad 1
    vq[0].push(pid);
    return;
}

void SchedNoMistery::unblock(int pid) {
    size_t idx;
    for (idx = 0; idx < unblock_to.size(); ++idx) {
        if (unblock_to[idx].first == pid)
            break;
    }

    if (unblock_to[idx].second > 1) {
        vq[unblock_to[idx].second - 1].push(pid);
    } else {
        vq[0].push(pid);
    }

    unblock_to.erase(find(unblock_to.begin(), unblock_to.end(),
                          std::pair<int, int>(pid, unblock_to[idx].first)));
    return;
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
    int pid_actual = current_pid(cpu);
    int pid_siguiente = pid_actual;
    switch (m) {
        case TICK:
            //se reduce el quantum
            quantum--;
            //si no tiene mas quantum y hay alguien en la cola de Prioridad 1
            if (quantum <= 0) {
                if (pid_actual != IDLE_TASK) {
                    //se agrega el que estaba corriendo al final de la cola de ready de una prioridad mayor
                    if ((int)vq.size() > cur_pri+1) {
                        vq[cur_pri+1].push(pid_actual);
                    } else {
                        vq[cur_pri].push(pid_actual);
                    }
                }
                //se elige el próximo a ejecutar
                pid_siguiente = SchedNoMistery::next();
            }
        break;
        case BLOCK:
            //se agrega a la lista de bloqueados
            unblock_to.push_back(std::make_pair(pid_actual, cur_pri));
            //se elige el próximo a ejecutar
            pid_siguiente = SchedNoMistery::next();
        break;
        case EXIT:
            //cout << "sale el " << pid_actual << endl;
            //se elige el próximo a ejecutar
            pid_siguiente = SchedNoMistery::next();
        break;
    }
    return pid_siguiente;
}

int SchedNoMistery::next(void) {
    // Elijo el nuevo pid
    int pid_siguiente = IDLE_TASK;
    int num_cola = 0;
    //se pasa el quantum a 0
    quantum = 0;
    while (num_cola < n && pid_siguiente == IDLE_TASK) {
        //si hay alguien en la cola de ready de Prioridad num_cola
        if (!vq[num_cola].empty()) {
            //se saca el primero
            pid_siguiente = vq[num_cola].front();
            vq[num_cola].pop();
            //se le vuelve a asignar el quantum inicial de Prioridad num_cola
            quantum = def_quantum[num_cola];
            cur_pri = num_cola;
        }
        num_cola++;
    }
    //cout << "se le da " << quantum << " al pid " << pid_siguiente << endl;
    return pid_siguiente;
}
