/*************************
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

*************************/

#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

// MAXSIZE = 20
Arena *cria_arena(int size){
	// cria o "array hexagonal"
	int i;
	int j;
	Arena arena;

	for(i = 0; i<size; i++){
		for(j=0;j<size;j+=2){
			if(i%2==0 && i>0 && j==0) j=1;
			arena->hexagon[i][j]->terreno = 1;
			arena->hexagon[i][j]->cristais = 0;
			arena->hexagon[i][j]->ocup = 0;
			arena->hexagon[i][j]->is_base = 0;
		}
	}

	return arena;
}

void atualiza(int ciclos){
	// move os robos e atualiza o status do sistema
}

void insere_exercito(int team){
	// insere novo exercito
}

void remove_exercito(int i, int j){
	// remove um robo derrotado
}

int sistema(int op){
	// especial call to coordenate the game
}





