main:main.o subset.o
	g++ main.o subset.o -std=c++11 -o main.exe
main.o:main.cpp AllSubsetSums.h
	g++ -c main.cpp -std=c++11 -o main.o
subset.o:AllSubsetSums.cpp AllSubsetSums.h
	g++ -c AllSubsetSums.cpp -std=c++11 -o subset.o		
.PHONY:clean run
clean:
	rm -rf db.o main.o main.exe
run:
	./main.exe