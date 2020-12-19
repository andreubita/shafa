CC = gcc
CFLAGS = -Wall -g
SRCS = src/Main.c src/moduloC/ModuloC.c src/moduloC/ModuloC.h #src/moduloT/ModuloT.c src/moduloT/ModuloT.h src/utils/Lista.c src/utils/Lista.h
OBJS = $(SRCS:.c=.o)
MAIN = shafa

.PHONY: depend clean

all:    $(MAIN)
	@echo  Shafa compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $^
