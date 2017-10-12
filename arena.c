/********************************

	Exemplo de arena (size = 9)
	0 = espaço vazio 
	1 = celula

	1 0 1 0 1 0 1 0 1
	0 1 0 1 0 1 0 1 0
	1 0 1 0 1 0 1 0 1
	0 1 0 1 0 1 0 1 0
	1 0 1 0 1 0 1 0 1
	0 1 0 1 0 1 0 1 0
	1 0 1 0 1 0 1 0 1
	0 1 0 1 0 1 0 1 0
	1 0 1 0 1 0 1 0 1

*********************************/

#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

#define hex (arena->hexagon)
#define rob (arena->robo)
#define tempo (arena->tempo)
#define pI (pos->i)
#define pJ (pos->j)

// define o numero de robos em cada exercito
#define NUMROBOS 10

Arena arena;

// MAXSIZE = 20
// inicializa a arena com todos os terrenos planos,
// sem cristais, bases ou exércitos
Arena *cria_arena(int size){
	int i;
	int j;

	for(i = 0; i<size; i++){
		for(j=0;j<size;j+=2){
			if(i%2==0 && i>0 && j==0) j=1;
			hex[i][j]->terreno = 1;
			hex[i][j]->cristais = 0;
			hex[i][j]->ocup = 0;
			hex[i][j]->is_base = 0;
		}
	}

	// inicializa os robos sem time
	for (int i = 0; i < NUMROBOS; i++){
		rob[i]->team = 0;
	}

	return arena;
}

// faz com que cada robo execute um numero certo de instruções(ciclos)
// avança o tempo
void atualiza(int ciclos){
	int i;
	for(i = 0; i < NUMROBOS; i++){
		if(rob[i]->hp > 0) // check if the robot is still active
			exec_maquina(rob[i], ciclos);
	}
	tempo+=ciclos;
}

// insere cada exercito t com os robos nas posiçoes
// dados no array p[] recebidos externamente
// numero de robos facilmente alteravel pelo parâmetro NUMROBOSS
void insere_exercito(int t, POSICAO p[]){
	// checa se t é o primeiro time ou o segundo
	int is_first = 1;
	if(rob[0]->team != t) is_first = 0;
	if(!is_first){
		for(int i = NUMROBOS/2; i<NUMROBOS; i++){
			rob[i]->team = t;
			rob[i]->hp = 100;
			rob[i]->pI = p[i]->i;
			rob[i]->pJ = p[i]->j;
			hex[rob[i]->pI][rob[i]->pJ]->ocup = 1;
		}
	}
	else{
		for(int i = 0; i < NUMROBOS/2; i++){
			rob[i]->team = t;
			rob[i]->hp = 100;
			rob[i]->pI = p[i]->i;
			rob[i]->pJ = p[i]->j;
			hex[rob[i]->pI][rob[i]->pJ]->ocup = 1;
		}
	}
		
}

void remove_exercito(int t){
	// remove um exercito derrotado
	int i;
	for(i = 0; i < NUMROBOS;i++){
		if(rob[i]->team == t) destroi_maquina(rob[i]);
		rob[i]->hp = 0;
		hex[rob[i]->pI][rob[i]->pJ]->ocup = 0;
	}
}

int sistema(int op){
	// especial call to coordenate the game
}





