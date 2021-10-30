cars: main.o car.o
	gcc -o cars main.o car.o

main.o: main.c car.h
	gcc -c main.c

car.o: car.c car.h
	gcc -c car.c