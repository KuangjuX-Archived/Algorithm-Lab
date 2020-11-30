main:main.o subset.o
	g++ main.o subset.o -o main.exe
main.o:main.cpp AllSubsetSums.h
	g++ -c main.cpp -o main.o
subset.o:AllSubsetSums.cpp AllSubsetSums.h
	g++ -c AllSubsetSums.cpp -o subset.o		
.PHONY:clean run
clean:
	rm -rf db.o main.o main.exe
run:
	./main.exe