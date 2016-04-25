#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	

	cpu_quantum.clear();
	def_quantum.clear();
	for (int i = 1; i < argn.size(); ++i){
		cpu_quantum.push_back(argn[i]);
		def_quantum.push_back(argn[i]);
	}
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	q.push(pid);
}

void SchedRR::unblock(int pid) {
	load(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	int siguiente;
	if (current_pid(cpu) == IDLE_TASK){
		if (!q.empty()){
			siguiente = q.front();
			q.pop();
		} else {
			siguiente = IDLE_TASK;
		}	
		return siguiente;
	} 

	if (m == EXIT || m == BLOCK){
		def_quantum[cpu] = cpu_quantum[cpu];
		if (!q.empty()){
			siguiente = q.front();
			q.pop();
		} else {
			siguiente = IDLE_TASK;
		}	
		return siguiente;
	}

	

	if (m == TICK){
		def_quantum[cpu]--;
		if (def_quantum[cpu] == 0){
			def_quantum[cpu] = cpu_quantum[cpu];
			q.push(current_pid(cpu));
			siguiente = q.front();
			q.pop();
		} else {
			siguiente = current_pid(cpu);
		}
		return siguiente;
	}
}
/*
int SchedRR::next(int cpu, const enum Motivo m){
	int siguiente;
	if (m == EXIT){
		if (!q.empty()){
			siguiente = q.front();
			q.pop();
		} else {
			siguiente = IDLE_TASK;
		}		
	} else {
		q.push(current_pid(cpu));
		if (!q.empty()){
			int volverEncolar = q.front();
			q.pop();
			siguiente = q.front();
		} else {
			siguiente = IDLE_TASK;
		}		
	}
	
	return siguiente;
}
*/

//<<<REMOVE>>>
