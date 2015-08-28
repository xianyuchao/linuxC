#cacu
cacu:add.o sub.o main.o
	gcc -o cacu add/add.o sub/sub.o main.o

#add.o
add.o:add/add.c	add/add.h
	gcc -c -o add/add.o add/add.c

#sub.o
sub.o:sub/sub.c sub/sub.h
	gcc -c -o sub/sub.o sub/sub.c

#main.o
main.o:main.c add/add.h sub/sub.h
	gcc -c -o main.o main.c -Iadd -Isub

clean:
	rm -f cacu add/*.o sub/*.o main.o

