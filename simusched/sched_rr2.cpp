#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro	
	for (int i = 0; i < argn[0]; ++i){
		queue<int> cola;		
		q.push_back(cola);
	}

	for (int i = 0; i < argn[0]; ++i){
		vector<int> tareas;
		tasks.push_back(tareas);
	}

	cpu_quantum.clear();
	def_quantum.clear();
	
	for (int i = 1; i <= argn[0]; ++i){		
		cpu_quantum.push_back(argn[i]);
		def_quantum.push_back(argn[i]);
	}
}

SchedRR2::~SchedRR2() {
}


void SchedRR2::load(int pid) {	
	int menor = q[0].size() ;	
	for (int i = 0; i < q.size(); ++i) {
		if(q[i].size()<menor){
			menor = i;
		}
	}		
	q[menor].push(pid);	
	tasks[menor].push_back(pid);		
}

void SchedRR2::unblock(int pid) {	
	int nucleo = -1;
	for (int i = 0; i < tasks.size(); ++i) {
		for (int j = 0; j < tasks[i].size(); ++j) {
			if(tasks[i][j] == pid);
			nucleo = i;
		}
	}
	q[nucleo].push(pid);
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
int siguiente;	
	if (current_pid(cpu) == IDLE_TASK){
		siguiente = next(cpu);			
		return siguiente;
	} 
	if (m == EXIT){
		def_quantum[cpu] = cpu_quantum[cpu];
		siguiente = next(cpu);		
		for (int i = 0; i < tasks.size(); ++i) {
			for (int j = 0; j < tasks[i].size(); ++j) {
				if(tasks[i][j] == current_pid(cpu)){
					tasks[i].erase(tasks[i].begin()+j);
				}
			}
		}
		return siguiente;
	}
	if (m == BLOCK){
		def_quantum[cpu] = cpu_quantum[cpu];
		siguiente = next(cpu);	
		return siguiente;			
	}
	if (m == TICK){
		def_quantum[cpu]--;
		if (def_quantum[cpu] == 0){
			def_quantum[cpu] = cpu_quantum[cpu];
			q[cpu].push(current_pid(cpu));
			siguiente = next(cpu);			
		} else {
			siguiente = current_pid(cpu);
		}
		return siguiente;		
	}	
	
}

int SchedRR2::next(int cpu) {
	int next;
	if (!q[cpu].empty()) {
		next = q[cpu].front();
		q[cpu].pop();
	} else {
		next = IDLE_TASK;
	}
	return next;	
}
