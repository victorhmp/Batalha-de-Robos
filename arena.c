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
#include <string.h>
#include "arena.h"

#define hex (arena->hexagon)
#define rob (arena->robo)
#define tempo (arena->tempo)

// define o numero de robos na arena
#define NUMROBOS 10
// define o numeros de instruções por ciclo
#define CICLOS 50

Arena *arena;

// MAXSIZE = 20, pode ser alterado em "arena.h"
// inicializa a arena com todos os atributos iniciais
Arena *cria_arena(int size, POSICAO *b[], POSICAO *c[], int n[], POSICAO *ter[]){
	
	int i;
	int j;

	for(i = 0; i<size; i++){
		for(j=0;j<size;j+=2){
			if(i%2==0 && i>0 && j==0) j=1;
			hex[i][j].terreno = 1;
			hex[i][j].cristais = 0;
			hex[i][j].ocup = 0;
			hex[i][j].is_base = 0;
		}
	}

	// atualiza o grid com o atributo is_base = 1 para as bases
	// recebidas via .txt fornecido quando o programa é executado
	// assume q a primeira base é do time 1 e a segunda do time 2
	hex[b[0]->i][b[0]->j].is_base = 1;
	//hex[b[0]->i][b[0]->j].team = 1;
	hex[b[0]->i][b[0]->j].ocup = 1;

	hex[b[1]->i][b[1]->j].is_base = 2;
	//hex[b[1]->i][b[1]->j].team = 2;
	hex[b[1]->i][b[1]->j].ocup = 1;

	// atualiza o grid com os cristais em suas posições
	// n[i] é o numero de cristais na posição c[i]
	int num_crist = sizeof(*c)/sizeof(c[0]);
	for (int k = 0; k < num_crist; k++){
		hex[c[k]->i][c[k]->j].cristais = n[k];
	}

	// atualiza o grid com os terrenos rugosos
	int num_terrenos = sizeof(*ter)/sizeof(ter[0]);
	for (int k = 0; k < num_crist; k++){
		hex[ter[k]->i][ter[k]->j].terreno = 3;
	}

	// inicializa os robos
	// serve como "função de registro"
	for (int i = 0; i < NUMROBOS; i++){
		// cada robo é inicializado com seu conjunto de instruções
		// rob[i] = cria_maquina(conjunto de instruções);
	}

	return arena;
}

// faz com que cada robo execute um numero certo de instruções(CICLOS)
// e avança o tempo
int ciclos = CICLOS;
void atualiza(int ciclos){
	int i;
	for(i = 0; i < NUMROBOS; i++){
		if(rob[i].hp > 0) // check if the robot is still active
			exec_maquina(&rob[i], ciclos);
	}
	tempo+=CICLOS;
}

// insere cada exercito t com os robos nas posiçoes
// dados no array p[] recebidos externamente (via .txt)
// numero de robos facilmente alteravel pelo parâmetro NUMROBOS
void insere_exercito(int t, POSICAO p[]){
	// checa se t é o primeiro time ou o segundo a ser adicionado
	int is_first = 1;
	if(rob[0].team != 0) is_first = 0;
	if(!is_first){
		for(int i = NUMROBOS/2; i<NUMROBOS; i++){
			rob[i].team = t;
			rob[i].hp = 100;
			rob[i].pos.i = p[i].i;
			rob[i].pos.j = p[i].j;
			hex[rob[i].pos.i][rob[i].pos.j].ocup = 1;
		}
	}
	else{
		for(int i = 0; i < NUMROBOS/2; i++){
			rob[i].team = t;
			rob[i].hp = 100;
			rob[i].pos.i = p[i].i;
			rob[i].pos.j = p[i].j;
			hex[rob[i].pos.i][rob[i].pos.j].ocup = 1;
		}
	}
		
}

// remove um exercito derrotado
void remove_exercito(int t){
	int i;
	for(i = 0; i < NUMROBOS;i++){
		if(rob[i].team == t) destroi_maquina(&rob[i]);
		rob[i].hp = 0;
		hex[rob[i].pos.i][rob[i].pos.j].ocup = 0;
	}
}

// Função recebe um int que codifica a instrução
// 1  = Mover / 2 = Recolhe / 3 = Deposita / arg >= 4 -> TipoAtaque
// o código para TipoAtaque já descreve seu alcance e sua força
// a força do ataque é 10 vezes o seu alcance, pode ser modificado futuramente
// Assume que o argumento é passado de maq.c pela instrução do robo
// Direção = SUL || NOR || NOD || SOE || SUD || NOE (baixo-cima-diagonais)
// return 1 se o sistema autorizar o que o robo pede
// return 0 se o sistema não autorizar
int sistema(int op, Maquina *robo, OPERANDO dir){
	POSICAO nova_pos;
	int force = op*10;
	if(strncmp(dir.val.aca.dir, "SUL", 3)==0){
		nova_pos.i = robo->pos.i + 2;
		nova_pos.j = robo->pos.j;
	}
	if(strncmp(dir.val.aca.dir, "NOR", 3)==0){
		nova_pos.i = robo->pos.i - 2;
		nova_pos.j = robo->pos.j;
	}
	if(strncmp(dir.val.aca.dir, "NOD", 3)==0){
		nova_pos.i = robo->pos.i - 1;
		nova_pos.j = robo->pos.j + 1;
	}
	if(strncmp(dir.val.aca.dir, "SOE", 3)==0){
		nova_pos.i = robo->pos.i + 1;
		nova_pos.j = robo->pos.j - 1;
	}
	if(strncmp(dir.val.aca.dir, "SUD", 3)==0){
		nova_pos.i = robo->pos.i + 1;
		nova_pos.j = robo->pos.j + 1;
	}
	if(strncmp(dir.val.aca.dir, "NOE", 3)==0){
		nova_pos.i = robo->pos.i - 1;
		nova_pos.j = robo->pos.j - 1;
	}

	switch(op){
		case 1:
			if( (hex[nova_pos.i][nova_pos.j].ocup) == 0){
				robo->pos.i = nova_pos.i;
				robo->pos.j = nova_pos.j;
				return 1;
			}
			else 
				return 0;
			break;
		case 2:
			if( (hex[nova_pos.i][nova_pos.j].cristais) > 0){
				robo->cristais += hex[nova_pos.i][nova_pos.j].cristais;
				(hex[nova_pos.i][nova_pos.j].cristais) = 0;
				return 1;
			}
			else
				return 0;
			break;
		case 3:
			if( (hex[nova_pos.i][nova_pos.j].ocup) == 0){
				(hex[nova_pos.i][nova_pos.j].cristais)++;
				robo->cristais--;
				return 1;
			}
			else
				return 0;
			break;
		// Por enquanto, alcance do ataque é igual a 1, por simplicidade.
		// Será modificado posteriormente
		default:
			//int force = op*10;
			if( (hex[nova_pos.i][nova_pos.j].ocup) == 1 ){
				for(int i=0;i<NUMROBOS;i++){
					if( (rob[i].pos.i == nova_pos.i) && (rob[i].pos.j == nova_pos.j) )
						rob[i].hp -= force; 
				}
			}
			return 1;
			break;
	}
	return 1;
}