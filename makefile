GCC=gcc
LDFLAGS=-lm
LIB=./lib
INCLUDE=./include
CFLAGS=-Wall -g
SRC=./src/*.c
OBJ=$(SRC:.c=.o)
EXEC=Sharethings

all:$(EXEC)

$(EXEC): $(OBJ) $(INCLUDE)/*.h
	$(GCC) $(CFLAGS) -o $(EXEC) ./src/personnes.c ./src/ressources.c ./src/menus.c -I$(INCLUDE) -L$(LIB) $(LDFLAGS)
	mv src/*.o lib

Sharethings.o: Sharethings.c
	$(GCC) $(CFLAGS) -o Sharethings.o -c ./src/Sharethings.c
	ls

personnes.o: personnes.c $(INCLUDE)/personnes.h
	$(GCC) $(CFLAGS) -o personnes.o -c ./src/personnes.c

ressources.o: ressources.c $(INCLUDE)/ressources.h
		$(GCC) $(CFLAGS) -o ressources.o -c ./src/ressources.c

menus.o: menus.c $(INCLUDE)/menus.h
	$(GCC) $(CFLAGS) -o menus.o -c ./src/menus.c

clean:
	rm $(EXEC)
	rm lib/*.o
