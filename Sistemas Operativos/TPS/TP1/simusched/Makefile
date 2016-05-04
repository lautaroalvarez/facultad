export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb -std=c++11 -O1 #-Wextra -Werror
LDFLAGS= -lpthread

OBJS= main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o 
NO_DELETE= sched_mistery.o 
MAIN= simusched

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS) $(NO_DELETE)
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -o $@ $^ $(LDFLAGS) 

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h
#sched_mistery.o: sched_mistery.h basesched.h
sched_no_mistery.o: sched_no_mistery.h basesched.h
cpu.o: cpu.cpp cpu.h

clean:
	rm -f $(OBJS) $(MAIN)

new: clean all

ejercicio1:
	./simusched Lotes/Lote_Tasks_Ej1.tsk 2 1 1 SchedRR | ./graphsched.py >> imagenes/imgEjercicio1.png

#
ejercicio2:
	./simusched Lotes/Lote_Tasks_Ej2.tsk 1 5 0 SchedFCFS | ./graphsched.py >> imagenes/imgEjercicio2_1core.png
	./simusched Lotes/Lote_Tasks_Ej2.tsk 1 5 0 SchedFCFS | ./graphsched.py >> imagenes/imgEjercicio2_2cores.png
	./simusched Lotes/Lote_Tasks_Ej2.tsk 1 5 0 SchedFCFS | ./graphsched.py >> imagenes/imgEjercicio2_4cores.png
	
ejercicio3:
	./simusched Lotes/Lote_Tasks_Ej3.tsk 2 1 1 SchedRR | ./graphsched.py >> imagenes/imgEjercicio3.png

ejercicio4:
	./simusched Lotes/Lote_Tasks_Ej4.tsk 2 1 1 SchedRR | ./graphsched.py >> imagenes/imgEjercicio4.png

ejercicio5:
	./simusched Lotes/Lote_Tasks_Ej5.tsk 1 2 0 SchedRR 2| ./graphsched.py >> imagenes/imgEjercicio5_q2.png
	./simusched Lotes/Lote_Tasks_Ej5.tsk 1 2 0 SchedRR 10| ./graphsched.py >> imagenes/imgEjercicio5_q10.png
	./simusched Lotes/Lote_Tasks_Ej5.tsk 1 2 0 SchedRR 50| ./graphsched.py >> imagenes/imgEjercicio5_q50.png

ejercicio6:
	./simusched Lotes/Lote_Tasks_Ej6.tsk 1 2 0 SchedFCFS | ./graphsched.py >> imagenes/imgEjercicio6.png

ejercicio7: simusched
	./simusched Lotes/ej7/lote1.tsk 1 1 1 SchedMistery 2 4 8 16 32 | python graphsched.py > imagenes/lote1_Mistery.png
	./simusched Lotes/ej7/lote1.tsk 1 1 1 SchedNoMistery 2 4 8 16 32 | python graphsched.py > imagenes/lote1_NoMistery.png
	./simusched Lotes/ej7/lote2.tsk 1 1 1 SchedMistery 2 4 8 16 32 | python graphsched.py > imagenes/lote2_Mistery.png
	./simusched Lotes/ej7/lote2.tsk 1 1 1 SchedNoMistery 2 4 8 16 32 | python graphsched.py > imagenes/lote2_NoMistery.png

ejercicio8: simusched
	./simusched Lotes/ej8/lote1.tsk 4 1 1 SchedRR2 8 8 8 8 | python graphsched.py > imagenes/lote1_sched.png
	./simusched Lotes/ej8/lote1.tsk 4 1 1 SchedRR2 8 8 8 8 | python graph_cores.py > /dev/null
	mv out_cores_timeline.png imagenes/lote1_cores.png
	./simusched Lotes/ej8/lote2.tsk 4 1 1 SchedRR2 8 8 8 8 | python graphsched.py > imagenes/lote2_sched.png
	./simusched Lotes/ej8/lote2.tsk 4 1 1 SchedRR2 8 8 8 8 | python graph_cores.py > /dev/null
	mv out_cores_timeline.png imagenes/lote2_cores.png

