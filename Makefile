all: cpusim

cpusim: main.o params.o multilevel.o rr.o sjf.o fifo.o event_q.o queue.o gentask.o
	gcc -o cpusim main.o params.o multilevel.o rr.o sjf.o fifo.o event_q.o queue.o gentask.o

params.o: params.c params.h
	gcc -c params.c

sjf.o: sjf.c params.h task.h queue.h event.h event_q.h
	gcc -c sjf.c

fifo.o: fifo.c params.h task.h queue.h event.h event_q.h
	gcc -c fifo.c

rr.o: rr.c params.h task.h queue.h event.h event_q.h
	gcc -c rr.c

multilevel.o: multilevel.c params.h task.h queue.h event.h event_q.h
	gcc -c multilevel.c

main.o: main.c params.h task.h event.h event_q.h gentask.h simulate.h
	gcc -c main.c

event_q.o: event_q.c task.h event.h event_q.h
	gcc -c event_q.c

queue.o: queue.c task.h queue.h
	gcc -c queue.c

gentask.o: gentask.c params.h task.h event.h event_q.h gentask.h
	gcc -c gentask.c

clean:
	rm -f *.o *~ cpusim
