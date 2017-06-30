state_facts: state_facts.o run_facts.o
	g++ -std=c++11 state_facts.o run_facts.o -o state_facts

state_facts.o: state_facts.cpp
	g++ -std=c++11 -c state_facts.cpp

run_facts.o: run_facts.cpp
	g++ -std=c++11 -c run_facts.cpp

clean:
	rm -f *.o state_facts
