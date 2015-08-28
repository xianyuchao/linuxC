all:recv send

recv:recv.o
	gcc -o recv recv.o

recv.o:recv.c
	gcc -c -o recv.o recv.c

	
send:send.o
	gcc -o send send.o

send.o:send.c
	gcc -c -o send.o send.c

clean:
	rm -f recv send *.o

