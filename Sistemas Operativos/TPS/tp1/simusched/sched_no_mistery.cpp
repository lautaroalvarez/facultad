#include <vector>
#include <queue>
#include <iostream>
#include "sched_no_mistery.h"
#include "basesched.h"

using namespace std;

//PRIORIDAD 1: 1 quantum
//		- inician acá
//		- cuando se bloquean los pasan a esta prioridad
//PRIORIDAD 2: N quantum
//		- una vez que ejecutan 1 vez se los pasa a esta prioridad

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	//se inicia el quantum default de la Prioridad 1 (1)
	def_quantum.push_back(1);
	//se inicia el quantum default de la Prioridad 1 (N)
	if (argn.size() > 1) {
		def_quantum.push_back(argn[1]);
	} else {
		def_quantum.push_back(1);
	}
	
	//se inicia la cola de ready Prioridad 1
	vq.push_back(std::queue<int>());
	//se inicia la cola de ready Prioridad 2
	vq.push_back(std::queue<int>());
	
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
	//se saca de la lista de bloqueados
	int j = 0;
	int encontrado = 0;
	while (j < unblock_to.size() && !encontrado) {
		if (unblock_to[j] == pid) {
			encontrado = 1;
		} else {
			j++;
		}
	}
	unblock_to.erase(unblock_to.begin()+j);
	//se agrega a la cola de Prioridad 1
	vq[0].push(pid);
	return;
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	//cpu debe ser siempre 0 (1 solo nucleo)
	int pid_actual = current_pid(0);
	int pid_siguiente = pid_actual;
	switch (m) {
		case TICK:
			//se reduce el quantum
			quantum--;
			//si no tiene mas quantum y hay alguien en la cola de Prioridad 1
			if (quantum <= 0) {
				//se elige el próximo a ejecutar
				pid_siguiente = SchedNoMistery::next();
				if (pid_siguiente == IDLE_TASK && pid_actual != IDLE_TASK) {
					pid_siguiente = pid_actual;
				} else if (pid_actual != IDLE_TASK) {
					//se agrega el que estaba corriendo al final de la cola de ready de Prioridad 2
					vq[1].push(pid_actual);
				}
			}
		break;
		case BLOCK:
			//se agrega a la lista de bloqueados
			unblock_to.push_back(pid_actual);
			//se elige el próximo a ejecutar
			pid_siguiente = SchedNoMistery::next();
		break;
		case EXIT:
			//se elige el próximo a ejecutar
			pid_siguiente = SchedNoMistery::next();
		break;
	}
	return pid_siguiente;
}

int SchedNoMistery::next(void) {
	// Elijo el nuevo pid
	int pid_actual = current_pid(0);
	int pid_siguiente;
	//si hay alguien en la cola de ready de Prioridad 1
	if (!vq[0].empty()) {
		//se saca el primero de la cola de ready de Prioridad 1
		pid_siguiente = vq[0].front();
		vq[0].pop();
		//se le vuelve a asignar el quantum inicial de Prioridad 1
		quantum = def_quantum[0];
	} else if (!vq[1].empty()) {
		//se saca el primero de la cola de ready de Prioridad 2
		pid_siguiente = vq[1].front();
		vq[1].pop();
		//se le vuelve a asignar el quantum inicial de Prioridad 2
		quantum = def_quantum[1];
	} else {
		//sino pasa al proceso idle
		pid_siguiente = IDLE_TASK;
		//sino pone quantum 0 para que en cuanto haya alguien pueda correr
		quantum = 0;
	}
	return pid_siguiente;
}
