# Makefile para facilitar organização em pastas

SRCDIR = ./src
INCDIR = ./include
OBJDIR=./obj


CC=gcc
CFLAGS=-I$(INCDIR)


_DEPS = maq.h pilha.h instr.h arena.h symrec.h
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

OBJ = $(OBJDIR)/motor.o $(OBJDIR)/maq.o $(OBJDIR)/arena.o $(OBJDIR)/pilha.o compila.tab.o lex.yy.o $(OBJDIR)/symrec.o $(OBJDIR)/acertos.o 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


compila: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -lm -lfl 

compila.tab.o: ./src/compila.y
	bison -d ./src/compila.y
	gcc -c compila.tab.c $(CFLAGS)

lex.yy.o: ./src/compila.l
	flex ./src/compila.l
	gcc -c lex.yy.c $(CFLAGS)

.PHONY: clean push
clean:
	rm -f motor $(OBJDIR)/*.o *.o lex.yy.c compila.tab.c compila.tab.h *~ compia

push:
	git add . && git commit && git push
