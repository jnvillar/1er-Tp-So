#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(){
	srand(time(NULL));
	FILE* out = fopen("LoteProcesos.tsk", "w");
	fprintf(out, "%s\n", "TaskCPU 500");
	int bloqueo1 = (rand()%4)+1;
	int bloqueo2 = (rand()%4)+1;
	int bloqueo3 = (rand()%4)+1;

	fprintf(out, "%s %d\n", "TaskIO 10", bloqueo1);
	fprintf(out, "%s %d\n", "TaskIO 20", bloqueo2);
	fprintf(out, "%s %d\n", "TaskIO 30", bloqueo3);

	
	fclose(out);
	return 0;
}