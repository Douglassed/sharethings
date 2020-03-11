GCC=gcc
LDFLAGS=-lm
LIB=./lib
INCLUDE=./include
CFLAGS= -g
SRC=./src/*.c
OBJ=$(SRC:.c=.o)
EXEC=Sharethings

all:$(EXEC)

$(EXEC): $(OBJ) $(INCLUDE)/*.h ./src/Sharethings.o
	gcc $(CFLAGS) -o $(EXEC) ./src/personnes.c -I$(INCLUDE) -L$(LIB) $(LDFLAGS)
	mv src/*.o lib

personnes.o: personnes.c $(INCLUDE)/personnes.h
	$(GCC) $(CFLAGS) -o personnes.o -c ./src/personnes.c

Sharethings.o: Sharethings.c $(INCLUDE)/*.h $(OBJ)
	$(GCC) $(CFLAGS) -o Sharethings.o -c ./src/Sharethings.c



clean:
	rm $(EXEC)
	rm lib/*.o
