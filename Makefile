# Makefile para facilitar organização em pastas

SRCDIR = ./src
INCDIR = ./include
OBJDIR=./obj


CC=gcc
CFLAGS=-I$(INCDIR)


DEPS = $(INCDIR)/maq.h $(INCDIR)/pilha.h $(INCDIR)/instr.h $(INCDIR)/arena.h $(INCDIR)/symrec.h

OBJ =   $(OBJDIR)/symrec.o $(OBJDIR)/acertos.o $(OBJDIR)/motor.o $(OBJDIR)/maq.o $(OBJDIR)/arena.o $(OBJDIR)/pilha.o


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

play: $(OBJDIR)/compila.tab.o $(OBJDIR)/lex.yy.o $(OBJ)  
	gcc -o $@ $^  -lm -ll $(CFLAGS)


$(OBJDIR)/compila.tab.o: ./src/compila.y $(INCDIR)/symrec.h
	bison -d ./src/compila.y
	mv compila.tab.c ./src && mv compila.tab.h ./include
	gcc -c -o $@ ./src/compila.tab.c $(CFLAGS) 
$(OBJDIR)/lex.yy.o: ./src/compila.l $(INCDIR)/compila.tab.h
	flex ./src/compila.l
	mv lex.yy.c ./src
	gcc -c -o $@ ./src/lex.yy.c $(CFLAGS)
.PHONY: clean push
clean:
	rm -f $(OBJDIR)/*.o *.o ./src/lex.yy.c ./src/compila.tab.c ./include/compila.tab.h *~ play

push:
	git add . && git commit && git push
