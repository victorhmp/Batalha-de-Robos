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
#define CICLOS 1000

Arena *arena;
FILE *display;
int r = -1;

// MAXSIZE = 20, pode ser alterado em "arena.h"
// inicializa a arena com todos os atributos iniciais
void cria_arena(int size){
    
    int i;
    int j;
    
    arena = malloc(sizeof(Arena));
    //if(!arena) Fatal("Erro na criação, falta de espaço.");
    
    arena->times = 1;
    
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
    hex[size-1][0].is_base = 1;
    //hex[b[0]->i][b[0]->j].team = 1;
    hex[size-1][0].ocup = 1;
    
    hex[0][size-1].is_base = 2;
    //hex[b[1]->i][b[1]->j].team = 2;
    hex[0][size-1].ocup = 1;
    
    // atualiza o grid com os cristais em suas posições
    // n[i] é o numero de cristais na posição c[i]
    int crist = (size*size)/8;
    for(int i=0;i<crist; i++){
        int valid = 0;
        int rand_intI, rand_intJ;
        while(!valid){
            rand_intI = rand() % size;
            rand_intJ = rand() % size;
            if(((rand_intJ % 2 == 0 && rand_intI % 2 == 0) || (rand_intI % 2 != 0 && rand_intJ % 2 != 0)) && (hex[rand_intI][rand_intJ].is_base==0)){
                valid = 1;
                hex[rand_intI][rand_intJ].cristais++;
            }
        }
    }
    *rob = malloc(NUMROBOS * sizeof(Maquina));
}

// faz com que cada robo execute um numero certo de instruções(CICLOS)
// e avança o tempo
void atualiza(){
    int i;
    for(i = 0; i < NUMROBOS; i++){
        if(rob[i]->hp > 0 && rob[i]!=NULL) // check if the robot is still active
            exec_maquina(rob[i], CICLOS);
        if(rob[i]->hp <= 0 && rob[i]!=NULL)
            destroi_maquina(rob[i]);
    }
    tempo++;
}

// insere cada exercito t com os robos nas posiçoes
// robos carregados com o mesmo conjunto de instruções
// numero de robos facilmente alteravel pelo parâmetro NUMROBOS
void insere_exercito(int size, INSTR *prog, int time){
    
    for (int k = 0; k < NUMROBOS; k++) {
        r++;
        rob[k] = cria_maquina(prog);
        rob[k]->team = arena->times;
        rob[k]->hp = 100;
        rob[k]->reg = r;
        
        if (time == 1) {
            switch (k) {
                case 0:
                    rob[k]->pos.i = size-3;
                    rob[k]->pos.j = 0;
                    break;
                case 1:
                    rob[k]->pos.i = size-5;
                    rob[k]->pos.j = 0;
                    break;
                case 2:
                    rob[k]->pos.i = size-2;
                    rob[k]->pos.j = 1;
                    break;
                case 3:
                    rob[k]->pos.i = size-1;
                    rob[k]->pos.j = 2;
                    break;
                case 4:
                    rob[k]->pos.i = size-3;
                    rob[k]->pos.j = 2;
                    break;
            }
        }
        else if (time == 2) {
            switch (k) {
                case 0:
                    rob[k]->pos.i = 2;
                    rob[k]->pos.j = size-1;
                    break;
                case 1:
                    rob[k]->pos.i = 4;
                    rob[k]->pos.j = size-1;
                    break;
                case 2:
                    rob[k]->pos.i = 1;
                    rob[k]->pos.j = size-2;
                    break;
                case 3:
                    rob[k]->pos.i = 0;
                    rob[k]->pos.j = size-3;
                    break;
                case 4:
                    rob[k]->pos.i = 2;
                    rob[k]->pos.j = size-5;
                    break;
            }
        }
        
        hex[rob[k]->pos.i][rob[k]->pos.j].ocup = 1;
    }
}

// remove um exercito derrotado
void remove_exercito(int t){
    int i;
    for(i = 0; i < NUMROBOS;i++){
        if(rob[i]->team == t) destroi_maquina(rob[i]);
        rob[i]->hp = 0;
        hex[rob[i]->pos.i][rob[i]->pos.j].ocup = 0;
    }
}

// Função recebe um int que codifica a instrução
// 1  = Mover / 2 = Recolhe / 3 = Deposita / arg >= 4 -> TipoAtaque
// o código para TipoAtaque já descreve seu alcance e sua força
// a força do ataque é 10 vezes o seu alcance, pode ser modificado futuramente
// Assume que o argumento (Direção) está no topo da pilha de dados
// Direção = SUL || NOR || NOD || SOE || SUD || NOE (baixo-cima-diagonais)
// return 1 se o sistema autorizar o que o robo pede
// return 0 se o sistema não autorizar

int sistema(int op, Maquina* robo, Dir dir){
    POSICAO nova_pos;
    POSICAO original_pos;
    int force = op*10;
    switch(dir) { // ADICIONADO
        case SUL:
        nova_pos.i = robo->pos.i + 2;
        nova_pos.j = robo->pos.j;
        break;
        case NOR:
        nova_pos.i = robo->pos.i - 2;
        nova_pos.j = robo->pos.j;
        break;
        case NOD:
        nova_pos.i = robo->pos.i - 1;
        nova_pos.j = robo->pos.j + 1;
        break;
        case SOE:
        nova_pos.i = robo->pos.i + 1;
        nova_pos.j = robo->pos.j - 1;
        break;
        case SUD:
        nova_pos.i = robo->pos.i + 1;
        nova_pos.j = robo->pos.j + 1;
        break;
        case NOE:
        nova_pos.i = robo->pos.i - 1;
        nova_pos.j = robo->pos.j - 1;
        break;
    }
    
    switch(op){
        case 1:
            if( (hex[nova_pos.i][nova_pos.j].ocup) == 0){
                original_pos.i = robo->pos.i;
                original_pos.j = robo->pos.j;
                robo->pos.i = nova_pos.i;
                robo->pos.j = nova_pos.j;
                fprintf(display, "%d %d %d %d %d\n",
                                  robo->reg, original_pos.i, original_pos.j, nova_pos.i, nova_pos.j);
                fflush(display);

                if(hex[original_pos.i][original_pos.j].cristais > 0){
                    fprintf(display, "cristal %d %d %d\n", original_pos.i, original_pos.j, hex[original_pos.i][original_pos.j].cristais);
                    fflush(display);
                }

                //Desocupar a célula que o robo saiu e ocupar a célula para qual o robo se moveu.
                hex[original_pos.i][original_pos.j].ocup = 0;            
                hex[nova_pos.i][nova_pos.j].ocup = 1;  
                return 1;
            }
            else{
                printf("Célula de destino ocupada.\n");
                return 0;
            }
            break;
        case 2:
            if( (hex[nova_pos.i][nova_pos.j].cristais) > 0){
                //Adiciona aos cristais carregados pelo robo o número de cristais presentes na célula alvo.
                robo->cristais += hex[nova_pos.i][nova_pos.j].cristais;
                hex[nova_pos.i][nova_pos.j].cristais = 0;//Zera os cristais na célula alvo.
                //Atualiza os cristais da célula alvo na interface gráfica.
                fprintf(display, "clean %d %d\n", nova_pos.i, nova_pos.j);
                fflush(display);
            }
            else if((hex[nova_pos.i][nova_pos.j].cristais) == 0){
                printf("Célula vazia.\n");
            }
            else
                return 0;
            break;
        case 3:
            if(hex[nova_pos.i][nova_pos.j].ocup == 0){ //Se a célula estiver desocupada.              
                hex[nova_pos.i][nova_pos.j].cristais += robo->cristais;     
                robo->cristais = 0;//Zerar os cristais carregados pelo robo.
                //printf("Depositou na celula [%1d][%1d].\n", tmp.x, tmp.y);
                //Atualiza o número de cristais na célula alvo na interface gráfica.
                fprintf(display, "cristal %d %d %d\n", nova_pos.i, nova_pos.j, hex[nova_pos.i][nova_pos.j].cristais);
                fflush(display);
                return 1;
                break;
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
                    if( (rob[i]->pos.i == nova_pos.i) && (rob[i]->pos.j == nova_pos.j) )
                    rob[i]->hp -= force; 
                }
            }
            return 1;
        break;
    }
    return 1;
}
