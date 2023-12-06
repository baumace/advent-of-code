exe: output
	gcc compile.o -o code 
	make clean

output: solution.c
	gcc -ansi -pedantic -g -c -o compile.o solution.c

clean:
	rm -rf *.o
