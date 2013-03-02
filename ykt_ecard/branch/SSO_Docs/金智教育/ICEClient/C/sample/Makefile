
CC=/usr/gcc32/bin/gcc -g
 
#export LD_LIBRARY_PATH=/home/csun/c/lib:$LD_LIBRARY_PATH
 
all : main
clean: 
	rm main 

main: main.c
	$(CC) -o main   main.c -L../lib -I../include -lIdstar 


