OSsim: main.o operation.o OS_functions.o PCB.o process.o
	g++ main.o operation.o OS_functions.o PCB.o process.o -o OSsim
main.o: main.cpp
	g++ -c main.cpp
operation.o: operation.cpp
	g++ -c operation.cpp
OS_functions.o: OS_functions.cpp
	g++ -c OS_functions.cpp
PCB.o: PCB.cpp
	g++ -c PCB.cpp
process.o: process.cpp
	g++ -c process.cpp 
clean:
	rm *.o OSsim
