default: 
	make all
	make clean 
	
all : preprocess compile assembly result  run

preprocess : part1.c
	gcc -E part1.c -o part1.i

compile : part1.c
	gcc -S part1.i -o part1.s

assembly : part1.s 
	gcc -c part1.s -o part1.o 

result : part1.o 
	gcc part1.o -o result 

run : result 
	./result
clean: 
	rm part1.i part1.s part1.o 
	rm result 
	
