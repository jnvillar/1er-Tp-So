export LC_ALL=C
CXXFLAGS= -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_mistery.o sched_no_mistery.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN) 
	

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

clean:
	ls *.o | grep -v sched_mistery.o | xargs rm -f --preserve-root
	rm -f simusched
	rm -rf Ejercicio1 Ejercicio2 Ejercicio3 Ejercicio5 Ejercicio6 Ejercicio7 Ejercicio8
	
new: clean all

Ejercicio1:
	mkdir Ejercicio1
	./simusched Tareas/ej1.tsk 1 1 1 SchedFCFS | python graphsched.py >> Ejercicio1/grafico.png

Ejercicio2:
	mkdir Ejercicio2
	g++ Tareas/ej2-input.cpp -o Tareas/ej2 
	./Tareas/ej2
	./simusched Tareas/ej2.tsk 1 5 5 SchedFCFS | python graphsched.py >> Ejercicio2/grafico.png
	./simusched Tareas/ej2.tsk 2 5 5 SchedFCFS | python graphsched.py >> Ejercicio2/grafico2.png
	./simusched Tareas/ej2.tsk 4 5 5 SchedFCFS | python graphsched.py >> Ejercicio2/grafico3.png

Ejercicio3:
	mkdir Ejercicio3
	./simusched Tareas/ej3.tsk 1 1 1 SchedFCFS | python graphsched.py >> Ejercicio3/grafico.png
	./simusched Tareas/ej3.tsk 2 1 1 SchedFCFS | python graphsched.py >> Ejercicio3/grafico2.png
	./simusched Tareas/ej3.tsk 4 1 1 SchedFCFS | python graphsched.py >> Ejercicio3/grafico3.png

Ejercicio4:
	# mkdir Ejercicio4

Ejercicio5:
	mkdir Ejercicio5
	./simusched Tareas/ej5.tsk 1 2 1 SchedRR 2 | python graphsched.py >> Ejercicio5/grafico.png
	./simusched Tareas/ej5.tsk 1 2 1 SchedRR 10 | python graphsched.py >> Ejercicio5/grafico2.png
	./simusched Tareas/ej5.tsk 1 2 1 SchedRR 30 | python graphsched.py >> Ejercicio5/grafico3.png

Ejercicio6:
	mkdir Ejercicio6
	./simusched Tareas/ej6.tsk 1 2 1 SchedFCFS | python graphsched.py >> Ejercicio6/grafico.png

Ejercicio7:
	mkdir Ejercicio7
	./simusched Tareas/ej7.tsk 1 1 1 SchedMistery 3 5 | python graphsched.py >> Ejercicio7/grafico.png

Ejercicio8:
	mkdir Ejercicio8
	./simusched Tareas/ej8-1.tsk 2 1 0 SchedRR2 5 5 | python graphsched.py >> Ejercicio8/grafico.png
	./simusched Tareas/ej8-1.tsk 2 1 0 SchedRR 5 5 | python graphsched.py >> Ejercicio8/grafico2.png
	./simusched Tareas/ej8-2.tsk 2 1 0 SchedRR2 5 5 | python graphsched.py >> Ejercicio8/grafico.png
	./simusched Tareas/ej8-2.tsk 2 1 0 SchedRR 5 5 | python graphsched.py >> Ejercicio8/grafico2.png
