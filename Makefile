# Makefile para facilitar organização em pastas

SRCDIR = ./src
INCDIR = ./include
OBJDIR=./obj


CC=gcc
CFLAGS=-I$(INCDIR)


_DEPS = maq.h pilha.h instr.h arena.h
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

OBJ = $(OBJDIR)/motor.o $(OBJDIR)/maq.o $(OBJDIR)/arena.o $(OBJDIR)/pilha.o

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

motor: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f motor $(OBJDIR)/*.o

