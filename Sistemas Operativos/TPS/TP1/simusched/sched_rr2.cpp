#include <vector>
#include <queue>
#include <algorithm> // Find o remove if
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	
	//se inician las N colas de ready (de N nucleos)
	ncores = argn[0];
	for (int j = 1; j <= ncores; j++) {
		//queue<int>* aux = new queue<int>();
		//q.push_back(aux);
		q.push_back(queue<int>());
		if ((int)argn.size() > j) {
			//si hay un argumento de quantum por nucleo
			def_quantum.push_back(argn[j]);
		} else if (argn.size() > 1) {
			//si hay un argumento de quantum general
			def_quantum.push_back(argn[1]);
		} else {
			//si no hay un argumento de quantum
			def_quantum.push_back(1);
		}
		//inicio el quantum del nucleo en 0
		cpu_quantum.push_back(0);
		//inicio la lista de tareas de cada nucleo
		//vector<int>* aux2 = new vector<int>();
		tasks.push_back(vector<int>());
	}
	//se setea el lastcpu como el último, para que arranque en el primero
	//lastcpu = ncores;
}

SchedRR2::~SchedRR2() {
    //for (size_t i = 0; i < q.size(); i++)
    //    delete q[i];
    //for (size_t i = 0; i < tasks.size(); i++)
    //    delete tasks[i];
}


void SchedRR2::load(int pid) {
	//averiguo a que nucleo mandarle
	int num_core = 0;
	int cant_proc = 0;
	for (int i = 0; i < ncores; i++) {
		if (i == 0 || (int)tasks[i].size() < cant_proc) {
			num_core = i;
			cant_proc = tasks[i].size();
		}
	}
	//cout << "Load: " << pid << " en el nucleo " << num_core << endl;
	//agrego la task a la lista de tareas
	tasks[num_core].push_back(pid);
	//agrego la task a la cola de ready del nucleo
	q[num_core].push(pid);
}

void SchedRR2::unblock(int pid) {
	//busco la tarea dentro de la lista de tareas de cada nucleo
	int i = 0;
	int suNucleo = -1;
	while (i < ncores && suNucleo < 0) {
		int j = 0;
		while (j < (int)tasks[i].size() && suNucleo < 0) {
			if (pid == tasks[i].at(j)) {
				suNucleo = i;
			}
			j++;
		}
		i++;
	}
	//agrego la task a la cola de ready del nucleo
	q[suNucleo].push(pid);
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	int pid_actual = current_pid(cpu);
	int pid_siguiente = pid_actual;
	switch (m) {
		case TICK:
			//se reduce el quantum
			cpu_quantum[cpu]--;
			//si no tiene mas quantum y hay alguien en la cola de ready de su nucleo
			if (cpu_quantum[cpu] <= 0) {
				if (pid_actual != IDLE_TASK) {
					//se agrega el que estaba corriendo al final de la cola de ready de una prioridad mayor
					q[cpu].push(pid_actual);
				}
				//se elige el próximo a ejecutar
				pid_siguiente = SchedRR2::next(cpu);
			}
		break;
		case BLOCK:
			//se elige el próximo a ejecutar
			pid_siguiente = SchedRR2::next(cpu);
		break;
		case EXIT:
			//lo sacamos de la lista de procesos de su nucleo
    		tasks[cpu].erase(std::find(tasks[cpu].begin(), tasks[cpu].end(), pid_actual));
			//se elige el próximo a ejecutar
			pid_siguiente = SchedRR2::next(cpu);
		break;
	}
	return pid_siguiente;
}

int SchedRR2::next(int cpu) {
	// Elijo el nuevo pid
	int pid_siguiente = IDLE_TASK;
	cpu_quantum[cpu] = 0;
	//si hay alguien en la cola de ready de su nucleo
	if (!q[cpu].empty()) {
		//se saca el primero de la cola de ready de su nucleo
		pid_siguiente = q[cpu].front();
		q[cpu].pop();
		//se le vuelve a asignar el quantum inicial de su nucleo
		cpu_quantum[cpu] = def_quantum[cpu];
	}
	return pid_siguiente;
}
