all : src/menus.o src/Sharethings.o
	gcc -o Sharethings src/menus.o src/Sharethings.o

src/menus.o : src/menus.c include/menus.h
	gcc -c src/menus.c -Wall -o src/menus.o 

src/Sharethings.o : src/Sharethings.c
	gcc -c src/Sharethings.c -Wall -o src/Sharethings.o
