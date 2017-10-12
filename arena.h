#include "maq.h"
#define MAXRO 100
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

typedef struct{
	// 1 = terreno plano 3 = terreno rugoso
	int terreno;
	// numero de cristais
	int cristals;
	int ocup;
	// 0 = não base / 1 = base time 1 / 2 = base time 2
	int is_base;
} Celula;

Arena cria_arena(int size);

void atualiza(int ciclos);

void insere_exercito(int team);

int sistema(int op);
