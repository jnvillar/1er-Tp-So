#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <algorithm>
#include <iostream>

using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {

	for (int i = 0; i < argn.size(); i++){
		def_quantum.push_back(argn[i]);
		cpu_quantum.push_back(argn[i]);
		queue<int> q;
		vq.push_back(q);
		
	}
	n = argn.size();

}

void SchedNoMistery::load(int pid) {
	vq[0].push(pid);
	unblock_to.push_back(0);
}

void SchedNoMistery::unblock(int pid) {
	int cola = unblock_to[pid];
	vq[cola].push(pid);

}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	int siguiente;
	int pid = current_pid(cpu);
	if (pid == IDLE_TASK){
		return next(cpu);
	} 

	if (m == EXIT){
		siguiente = next(cpu);
					
		return siguiente;
	}

	if (m == BLOCK){
		unblock_to[pid] = max(unblock_to[pid]-1, 0);		
		return next(cpu);
	}

	if (m == TICK){
		def_quantum[cpu]--;
		if (def_quantum[cpu] == 0){
			
			unblock_to[pid] = min(unblock_to[pid]+1, n-1);
			vq[unblock_to[pid]].push(current_pid(cpu));
			
			siguiente = next(cpu);
		} else {
			siguiente = current_pid(cpu);
		}
		return siguiente;
	}

}

int SchedNoMistery::next(int cpu) {
	int siguiente;
	for (int i = 0; i<n; i++){
		if (!vq[i].empty()){
			siguiente = vq[i].front();
			vq[i].pop();
			def_quantum[cpu] = cpu_quantum[i];
			return siguiente;
		}	
	}
	
	return IDLE_TASK;
	
	
}
