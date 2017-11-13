#include "maq.h"
#define MAXRO 50
#define MAXSIZE 20

typedef struct{
	// array com os exercitos ativos
	// a posicao de cada robo é um parametro
	// da maquina virtual
	Maquina robo[MAXRO];

	int tempo;
	// array que representa a arena
	Celula hexagon[MAXSIZE][MAXSIZE];
} Arena;

void cria_arena(int size, INSTR *prog);

void atualiza(int ciclos);

void insere_exercito(int t, POSICAO p[]);

int sistema(int op, Maquina *robo, Dir dir);

extern Arena *arena;
