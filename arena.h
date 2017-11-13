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



Arena *cria_arena(int size, POSICAO *c[], int n[], POSICAO *ter[]);

void atualiza(int ciclos);

void insere_exercito(int t, POSICAO p[]);

int sistema(int op, Maquina *robo, OPERANDO dir);

extern Arena *arena;
