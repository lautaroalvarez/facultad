#include "tasks.h"
#include <random>
#include <utility>
#include <iostream> 

using namespace std;

const char bloquea = 1;
const char no_bloquea = 0;

void TaskCPU(int pid, vector<int> params) { // params: n
    uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
    uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
    uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
    for(int i = 0; i < (int)params.size(); i++) {
        if (i % 2 == 0) uso_CPU(pid, params[i]);
        else uso_IO(pid, params[i]);
    }
}

void TaskConsola(int pid, vector<int> params) {
    size_t n = params[0];
    size_t bmin = params[1];
    size_t bmax = params[2];
    std::random_device rd;
    std::mt19937 mt(rd()); //Distribuye en el rango pedido
    std::uniform_int_distribution<int> dist(bmin, bmax);

    for (size_t i = 0; i < n; i++) {
        uso_IO(pid, dist(mt));
    }
}

void TaskBatch(int pid, vector<int> params) {
    size_t total_cpu = params[0];
    size_t cant_bloqueos = params[1];       
    // Vamos a tener un vector que indica si es cpu o IO       
    // Como IO toma 2 ciclos lo shifteamos una vez a la izquierda.          
    std::random_device rd;
    std::mt19937 mt(rd()); //Distribuye en el rango pedido
    std::uniform_int_distribution<int> dist(0, total_cpu - 1);
    // Vector de bloqueos para saber en que ciclos bloquear
    // Si es true bloquea 2 ciclos de IO, sino es un ciclo de CPU.
    std::vector<char> bloqueos;  
    bloqueos.reserve(total_cpu);

    // Seteamos todos los valores del vector en 0
    for (size_t i = 0; i < total_cpu; ++i) {
        if (i < cant_bloqueos)
            bloqueos.push_back(bloquea);
        else 
            bloqueos.push_back(no_bloquea);
    }

    for (size_t i = 0; i < total_cpu; ++i) {
        int temp;
        int idx = dist(mt);
        int idx2 = dist(mt);
        temp = bloqueos[idx];
        bloqueos[idx] = bloqueos[idx2];
        bloqueos[idx2] = temp;
    }

    for(size_t i = 0; i < bloqueos.size(); ++i) {
        if (bloqueos[i] == bloquea) {
            uso_IO(pid, 4);
        } else {
            uso_CPU(pid, 1);
        }
    }
}

void tasks_init(void) {
    /* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
     * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
     * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
    register_task(TaskCPU, 1);
    register_task(TaskIO, 2);
    register_task(TaskAlterno, -1);
    register_task(TaskConsola, 3);
    register_task(TaskBatch, 2);
}
