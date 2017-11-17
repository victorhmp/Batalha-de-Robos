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
#define NUMROBOS 5
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
    // assume q a primeira base é do time 1 e a segunda do time 2
    hex[0][0].is_base = 1;
    hex[0][0].ocup = 1;
    fprintf(display, "base visual/base.png 0 %d %d\n", 0, 0);

    hex[11][11].is_base = 2;
    hex[11][11].ocup = 1;
    fprintf(display, "base visual/base.png 1 %d %d\n", 11, 11);

    fflush(display);

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
                printf("Cristal adicionado em %d %d\n", rand_intI, rand_intJ);
                fprintf(display, "cristal %d %d %d\n", rand_intI, rand_intJ, hex[rand_intI][rand_intJ].cristais);
                fflush(display);
            }
        }
    }
    *rob = malloc(NUMROBOS * sizeof(Maquina));
}

// faz com que cada robo execute um numero certo de instruções(CICLOS)
// e avança o tempo
void atualiza(int rodadas){
    int i;
    for(int t = 0;t<rodadas;t++){
        for(i = 0; i < 2*NUMROBOS; i++){
            if(rob[i]->hp > 0 && rob[i]!=NULL) // check if the robot is still active
                exec_maquina(rob[i], CICLOS);
            if(rob[i]->hp <= 0 && rob[i]!=NULL)
                destroi_maquina(rob[i]);
        }
        tempo++;
    }
}

// insere cada exercito t com os robos nas posiçoes
// robos carregados com o mesmo conjunto de instruções
// numero de robos facilmente alteravel pelo parâmetro NUMROBOS
void insere_exercito(int size, INSTR *rob0, INSTR *rob1, INSTR *rob2, INSTR *rob3, INSTR *rob4, int time){

    for (int k = 0; k < NUMROBOS; k++) {

        if (time == 1) {
            switch (k) {
                //rob[k]->reg = r++;
                case 0:
                    rob[k] = cria_maquina(rob0);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100-k;
                    rob[k]->pos.i = size-3;
                    rob[k]->pos.j = 0;
                    rob[k]->reg = 0;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
                case 1:
                    rob[k] = cria_maquina(rob1);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100-k;
                    rob[k]->pos.i = size-5;
                    rob[k]->pos.j = 0;
                    rob[k]->reg = 1;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
                case 2:
                    rob[k] = cria_maquina(rob2);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100-k;
                    rob[k]->pos.i = size-2;
                    rob[k]->pos.j = 1;
                    rob[k]->reg = 2;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
                case 3:
                    rob[k] = cria_maquina(rob3);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100-k;
                    rob[k]->pos.i = size-1;
                    rob[k]->pos.j = 2;
                    rob[k]->reg = 3;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
                case 4:
                    rob[k] = cria_maquina(rob4);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100-k;
                    rob[k]->pos.i = size-3;
                    rob[k]->pos.j = 2;
                    rob[k]->reg = 4;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
            }
        }
        else if (time == 2) {
            switch (k) {
                rob[k + NUMROBOS]->reg = r++;
                case 0:
                    rob[k + NUMROBOS] = cria_maquina(rob0);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100-k;
                    rob[k + NUMROBOS]->pos.i = 2;
                    rob[k + NUMROBOS]->pos.j = size-1;
                    rob[k + NUMROBOS]->reg = 5;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
                case 1:
                    rob[k + NUMROBOS] = cria_maquina(rob1);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100-k;
                    rob[k + NUMROBOS]->pos.i = 4;
                    rob[k + NUMROBOS]->pos.j = size-1;
                    rob[k + NUMROBOS]->reg = 6;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
                case 2:
                    rob[k + NUMROBOS] = cria_maquina(rob2);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100-k;
                    rob[k + NUMROBOS]->pos.i = 1;
                    rob[k + NUMROBOS]->pos.j = size-2;
                    rob[k + NUMROBOS]->reg = 7;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
                case 3:
                    rob[k + NUMROBOS] = cria_maquina(rob3);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100-k;
                    rob[k + NUMROBOS]->pos.i = 0;
                    rob[k + NUMROBOS]->pos.j = size-3;
                    rob[k + NUMROBOS]->reg = 8;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
                case 4:
                    rob[k + NUMROBOS] = cria_maquina(rob4);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100-k;
                    rob[k + NUMROBOS]->pos.i = 2;
                    rob[k + NUMROBOS]->pos.j = size-3;
                    rob[k + NUMROBOS]->reg = 9;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
            }
            /*fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
            fflush(display);
            */
        }

        hex[rob[k]->pos.i][rob[k]->pos.j].ocup = 1;
        //printf("Robo %d, do time %d adicionado OK \n", i, arena->times);
        //printf("time: %d, hp: %d, posição: %d %d\n", rob[i]->team, rob[i]->hp, rob[i]->pos.i, rob[i]->pos.j);
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
                hex[nova_pos.i][nova_pos.j].cristais = 0;

                //Atualiza os cristais da célula alvo na interface gráfica.
                fprintf(display, "erase %d %d\n", nova_pos.i, nova_pos.j);
                fflush(display);

            }
            else if((hex[nova_pos.i][nova_pos.j].cristais) == 0){
                printf("Célula vazia.\n");
                return 0;
            }
            else
                return 0;
            break;
        case 3:
            if(hex[nova_pos.i][nova_pos.j].ocup == 0){
                hex[nova_pos.i][nova_pos.j].cristais += robo->cristais;
                robo->cristais = 0;

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
