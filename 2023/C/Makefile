# target all means all targets currently defined in this file
all: lab2.zip bit_encode1 bit_encode2

# this target is the bit cipher executable that requires redirected stdin
compile: compile.o
	gcc compile.o -o code 

# this target is the dependency for bit_encode1
compile.o: day1.c
	gcc -ansi -pedantic -g -c -o compile.o day1.c

# this target deletes all files produced from the Makefile
# so that a completely new compile of all items is required
clean:
	rm -rf *.o bit_encode1 bit_encode2 lab2.zip
