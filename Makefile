GCC=gcc
LDFLAGS=-lm
LIB=./lib
INCLUDE=./include
CFLAGS= -g
SRC=./src
OBJ=$(SRC:.c=.o)
EXEC=Sharethings

all:$(EXEC)

$(EXEC): $(INCLUDE)/*.h total
	mv src/*.o lib
	gcc $(CFLAGS) -o $(EXEC) $(LIB)/*.o -I$(INCLUDE) -L$(LIB) $(LDFLAGS)


total: $(INCLUDE)/*.h $(OBJ)
	$(GCC) $(CFLAGS) -c $(SRC)/*.c


clean:
	rm $(EXEC)
	rm lib/*.o
