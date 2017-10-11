/***********************

Prototipo da arena

***********************/
#include "maq.h"
#define MAXRO 100
#define MAXSIZE 20


typedef struct{
	int robots[MAXRO];
	int time;

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

typedef struct{
	// position
	int i;
	int j;
} ROBOT;
