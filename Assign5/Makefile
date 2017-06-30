compiler: compiler.o list.o
	gcc compiler.o list.o -o compiler

queues: queues.o list.o
	gcc queues.o list.o -lm -o queue_compare

poisson_test: poisson_test.c
	gcc poisson_test.c -lm -o poisson_test

compiler.o: compiler.c
	gcc -c compiler.c

queues.o: queues.c
	gcc -c queues.c

list.o: list.c
	gcc -c list.c

clean:
	rm -f *.o queue_compare compiler poisson_test
