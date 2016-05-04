#include <vector>
#include <queue>
#include <iostream>
#include "sched_rr.h"
#include "basesched.h"

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
    cpu_quantum.reserve(argn[0]);
    def_quantum.reserve(argn[0]);
    for (size_t i = 1; i < argn.size(); ++i) {
        cpu_quantum.push_back(argn[i]);
        def_quantum.push_back(argn[i]);
    }
}

SchedRR::~SchedRR() {}

void SchedRR::load(int pid) {
    q.push(pid);
}

void SchedRR::unblock(int pid) {
    q.push(pid);
}

int SchedRR::tick(int id_cpu, const enum Motivo m) {
    int pid_ret = IDLE_TASK;
    int pid_c = current_pid(id_cpu);
    /* Si es un tick y no es la tarea idle vamos a ver si la tarea actual termino
     * o todavia tiene para ejecutar. Si pasa eso hacemos el cambio de contexto.
     * Si no era un tick o era la idle, solo vamos a intentar cargar un proceso nuevo,
     * de no haberlo sigue ejecutando la idle.
     */
    if (m == TICK && pid_c != IDLE_TASK) {
        cpu_quantum[id_cpu]--;
        if (cpu_quantum[id_cpu] == 0 && !q.empty()) {
            q.push(pid_c);
            pid_ret = q.front();
            q.pop();
            cpu_quantum[id_cpu] = def_quantum[id_cpu];
        } else {
            pid_ret = pid_c;
            if (!cpu_quantum[id_cpu]) cpu_quantum[id_cpu] = def_quantum[id_cpu];
        }
    } else {
        if (!q.empty()) {
            pid_ret = q.front();
            q.pop();
            cpu_quantum[id_cpu] = def_quantum[id_cpu];
        }
    }
    return pid_ret;
}
