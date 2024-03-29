#include "tasks.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>


using namespace std;

/* OBSERVACIONES

Las nuevas tareas deben ser registadas en task_init.
Las nuevas tareas deben ejecutar return para terminar
return: Tarda un quantum en salir
uso_CPU: Tiempo de ejecución.
uso_IO: Tiempo que va a pasar bloqueado. Primero utiliza un seg para bloquearse y luego se bloquea por el tiempo indicado

*/

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

	srand (time(NULL)); // semilla
	int tiempo; 

	/* N llamadas */
	for (int i = 0; i < params[0]; ++i) {
		tiempo = (rand() % (params[2]-params[1]+1)) + params[1]; // numero random entre bmin y bmax. Asumimos que no puede ser 0
		uso_IO(pid,tiempo);
	}

}


void TaskBatch(int pid, vector<int> params) {

	int cant_bloqueos = params[1];
	int tiempo_cpu = params[0];
	srand (time(NULL)); // semilla
	vector<int> tiempos(cant_bloqueos,0);
	
	for (int i = 0; i < cant_bloqueos; i++) {
		tiempos[i]=(rand()%(tiempo_cpu-1-cant_bloqueos));
	}
	sort(tiempos.begin(), tiempos.end());
	for (int i = 1; i < cant_bloqueos; i++) {
		tiempos[cant_bloqueos-i] -= tiempos[cant_bloqueos-i-1];		
	}

	int restante = tiempo_cpu-1-cant_bloqueos;
	
	for (int i = 0; i < cant_bloqueos; i++){
		if (tiempos[i] != 0) {
			uso_CPU(pid,tiempos[i]);
			restante -= tiempos[i];
		}		
		uso_IO(pid,2);
	}
	
	if (restante != 0){
		uso_CPU(pid,restante);
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
