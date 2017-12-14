#include "compila.tab.h"
#include "maq.h"
#define MAXRO 50
#define MAXSIZE 20

typedef struct{
    // array com os exercitos ativos
    // a posicao de cada robo é um parametro
    // da maquina virtual
    Maquina* robo[MAXRO];
    int tempo;
    // array que representa a arena
    Celula hexagon[MAXSIZE][MAXSIZE];
    // numero de times na arena
    int times;
} Arena;

extern Arena *arena;
extern FILE *display;

void cria_arena(int size);

void atualiza();

void insere_exercito(int size, int time);

extern int sistema(int op, Maquina* robo, char *dir);

int compilador(FILE *, INSTR *);
