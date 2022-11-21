OSsim: main.o operation.o OS_functions.o PCB.o process.o
	g++ main.o operation.o OS_functions.o PCB.o process.o frame.o -o OSsim
main.o: main.cpp
	g++ -c main.cpp
frame.o: frame.o
	g++ -c frame.cpp frame.h
operation.o: operation.cpp
	g++ -c operation.cpp operation.h
OS_functions.o: OS_functions.cpp
	g++ -c OS_functions.cpp OS_functions.h
PCB.o: PCB.cpp
	g++ -c PCB.cpp 
process.o: process.cpp
	g++ -c process.cpp process.h 
clean:
	rm *.o OSsim
