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

// variáveis globais
Arena *arena;
FILE *display;

// variáveis auxiliares
int r = -1;
int k = 0;

// MAXSIZE = 20, pode ser alterado em "arena.h"
// inicializa a arena com todos os atributos iniciais
void cria_arena(int size){

    int i;
    int j;

    // aloca espaço de memória para a arena
    arena = malloc(sizeof(Arena));

    // inicia o número de times da arena
    arena->times = 1;

    // inicializa as células da arena
    for(i = 0; i<size; i++){
        for(j=0;j<size;j++){
            hex[i][j].terreno = 1;
            hex[i][j].cristais = 0;
            hex[i][j].ocup = 0;
            hex[i][j].is_base = 0;
        }
    }

    // atualiza o grid com o atributo is_base = 1 para as bases
    // assume q a primeira base é do time 1 e a segunda do time 2
    // já envia o protocolo de criação das bases na interface gráfica.
    hex[size-1][0].is_base = 1;
    hex[size-1][0].ocup = 1;
    fprintf(display, "base visual/base.png 0 %d %d\n", size-1, 0);
    hex[0][size-1].is_base = 2;
    hex[0][size-1].ocup = 1;
    fprintf(display, "base visual/base2.png 1 %d %d\n", 0, size-1);
    fflush(display);

    // distribui aleatóriamente as células especiais, que geram penalidades
    // quando ocupadas. Já desenha cada célula de acordo com seu valor
    // de penalidade.
    int especial_cells = 50;
    for(int i=0;i<especial_cells; i++){
        int valid = 0;
        int rand_intI, rand_intJ;
        while(!valid){
            rand_intI = rand() % size;
            rand_intJ = rand() % size;
            if(((rand_intJ % 2 == 0 && rand_intI % 2 == 0) || (rand_intI % 2 != 0 && rand_intJ % 2 != 0)) && (hex[rand_intI][rand_intJ].is_base==0)){
                valid = 1;
                int terr = rand() % 4;
                if(terr != 0) hex[rand_intI][rand_intJ].terreno = terr;
                else  hex[rand_intI][rand_intJ].terreno = 1;

                hex[rand_intI][rand_intJ].ocup = 0;

                if(terr == 1){
                    fprintf(display, "cel %d %d 232 159 113\n", rand_intI, rand_intJ);
                    fflush(display);
                }
                if(terr == 2){
                    fprintf(display, "cel %d %d 193 156 77\n", rand_intI, rand_intJ);
                    fflush(display);
                }
                if(terr == 3){
                    fprintf(display, "cel %d %d 119 167 214\n", rand_intI, rand_intJ);
                    fflush(display);
                }
                if(terr == 4){
                    fprintf(display, "cel %d %d 200 200 200\n", rand_intI, rand_intJ);
                    fflush(display);
                }
            }
        }
    }

    // atualiza o grid com os cristais em suas posições geradas aleatóriamente
    // já desenhando cada cristal em sua posição na interface gráfica
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
                //printf("Cristal adicionado em %d %d\n", rand_intI, rand_intJ);
                fprintf(display, "erase %d %d\n", rand_intI, rand_intJ);
                fprintf(display, "cristal %d %d %d\n", rand_intI, rand_intJ, hex[rand_intI][rand_intJ].cristais);
                fflush(display);
            }
        }
    }

    // aloca espaço para o vetor de robôs da arena
    *rob = malloc(NUMROBOS * sizeof(Maquina));
}

// faz com que cada robo execute um numero certo de instruções (definido em CICLOS)
// verificando se o robô está ocupado por penalidade ou está livre
// caso não esteja livre, diminuo sua penalidade e ele não executa o comando.
void atualiza(int rodadas){
    int i;
    for(int t = 0;t<rodadas;t++){
        for(i = 0; i < 2*NUMROBOS; i++){
            if(rob[i]->hp > 0 && rob[i]!=NULL){
                if(rob[i]->counter != 0){
                    printf("Robô ocupado.\n");
                    rob[i]->counter--;
                }
                else{
                    exec_maquina(rob[i], CICLOS);
                }
            }
            if(rob[i]->hp <= 0 && rob[i]!=NULL)
                destroi_maquina(rob[i]);
        }
        tempo++;
    }
}

// insere um exército com os robos nas posiçoes iniciais, já na interface gráfica
// as insruções de cada robô são passadas como argumento da função
// os robôs são também registrados pela arena no vetor de robôs
// assim que o robô é adicionado, a célula é marcada como ocupada
void insere_exercito(int size, int time){

    INSTR p1[2000];
    INSTR p2[2000];
    INSTR p3[2000];
    INSTR p4[2000];
    INSTR p5[2000];
    INSTR p6[2000];
    INSTR p7[2000];
    INSTR p8[2000];
    INSTR p9[2000];
    INSTR p10[2000];
    
    char program[10][3] = {{"p1"}, {"p2"}, {"p3"}, {"p4"}, {"p5"}, {"p6"}, {"p7"}, {"p8"}, {"p9"}, {"p0"}};
    
    for (int k = 0; k < NUMROBOS; k++) {

        if (time == 1) {
            
            FILE *p = fopen(program[k], "r");
            int res;
            
            switch (k) {
                case 0:
                    res = compilador(p, p1);
                    rob[k] = cria_maquina(p1);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100;
                    rob[k]->pos.i = size-3;
                    rob[k]->pos.j = 0;
                    rob[k]->reg = 0;
                    hex[rob[k]->pos.i][rob[k]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
                case 1:
                    res = compilador(p, p2);
                    rob[k] = cria_maquina(p2);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100;
                    rob[k]->pos.i = size-5;
                    rob[k]->pos.j = 0;
                    rob[k]->reg = 1;
                    hex[rob[k]->pos.i][rob[k]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
                case 2:
                    res = compilador(p, p3);
                    rob[k] = cria_maquina(p3);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100;
                    rob[k]->pos.i = size-2;
                    rob[k]->pos.j = 1;
                    rob[k]->reg = 2;
                    hex[rob[k]->pos.i][rob[k]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
                case 3:
                    res = compilador(p, p4);
                    rob[k] = cria_maquina(p4);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100;
                    rob[k]->pos.i = size-1;
                    rob[k]->pos.j = 2;
                    rob[k]->reg = 3;
                    hex[rob[k]->pos.i][rob[k]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
                case 4:
                    res = compilador(p, p5);
                    rob[k] = cria_maquina(p5);
                    rob[k]->team = arena->times;
                    rob[k]->hp = 100;
                    rob[k]->pos.i = size-3;
                    rob[k]->pos.j = 2;
                    rob[k]->reg = 4;
                    hex[rob[k]->pos.i][rob[k]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboA.png %d %d %d\n", rob[k]->reg++, rob[k]->pos.i, rob[k]->pos.j);
                    fflush(display);
                    break;
            }
            
            fclose(p);
        }
        else if (time == 2) {
            
            FILE *p = fopen(program[k+NUMROBOS], "r");
            int res;
            arena->times = 2;
            switch (k) {
                rob[k + NUMROBOS]->reg = r++;
                case 0:
                    res = compilador(p, p6);
                    rob[k + NUMROBOS] = cria_maquina(p6);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100;
                    rob[k + NUMROBOS]->pos.i = 2;
                    rob[k + NUMROBOS]->pos.j = size-1;
                    rob[k + NUMROBOS]->reg = 5;
                    hex[rob[k + NUMROBOS]->pos.i][rob[k + NUMROBOS]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
                case 1:
                    res = compilador(p, p7);
                    rob[k + NUMROBOS] = cria_maquina(p7);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100;
                    rob[k + NUMROBOS]->pos.i = 4;
                    rob[k + NUMROBOS]->pos.j = size-1;
                    rob[k + NUMROBOS]->reg = 6;
                    hex[rob[k + NUMROBOS]->pos.i][rob[k + NUMROBOS]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
                case 2:
                    res = compilador(p, p8);
                    rob[k + NUMROBOS] = cria_maquina(p8);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100;
                    rob[k + NUMROBOS]->pos.i = 1;
                    rob[k + NUMROBOS]->pos.j = size-2;
                    rob[k + NUMROBOS]->reg = 7;
                    hex[rob[k + NUMROBOS]->pos.i][rob[k + NUMROBOS]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
                case 3:
                    res = compilador(p, p9);
                    rob[k + NUMROBOS] = cria_maquina(p9);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100;
                    rob[k + NUMROBOS]->pos.i = 0;
                    rob[k + NUMROBOS]->pos.j = size-3;
                    rob[k + NUMROBOS]->reg = 8;
                    hex[rob[k + NUMROBOS]->pos.i][rob[k + NUMROBOS]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
                case 4:
                    res = compilador(p, p10);
                    rob[k + NUMROBOS] = cria_maquina(p10);
                    rob[k + NUMROBOS]->team = arena->times;
                    rob[k + NUMROBOS]->hp = 100;
                    rob[k + NUMROBOS]->pos.i = 2;
                    rob[k + NUMROBOS]->pos.j = size-3;
                    rob[k + NUMROBOS]->reg = 9;
                    hex[rob[k + NUMROBOS]->pos.i][rob[k + NUMROBOS]->pos.j].ocup = 1;
                    fprintf(display, "rob visual/roboB.png %d %d %d\n", rob[k + NUMROBOS]->reg, rob[k + NUMROBOS]->pos.i, rob[k + NUMROBOS]->pos.j);
                    fflush(display);
                    break;
            }
            
            fclose(p);
        }
    }
}


// remove um exercito derrotado do vetor de registro
// tira os robôs do exército da interface gráfica
void remove_exercito(int t){
    int i;
    for(i = 0; i < NUMROBOS;i++){
        if(rob[i]->team == t){
            hex[rob[i]->pos.i][rob[i]->pos.j].ocup = 0;
            fprintf(display, "clean %d %d\n", rob[i]->pos.i, rob[i]->pos.j);
            destroi_maquina(rob[i]);
        }
    }
}

// Função recebe um int que codifica a instrução
// 1  = Mover / 2 = Recolhe / 3 = Deposita / 4 = TipoAtaque
// a força do ataque é de 10 , pode ser modificado futuramente.
// Assume que o argumento (Direção) está no topo da pilha de dados
// Direção =  LES || OES || NOD || SOE || SUD || NOE (leste-oeste e diagonais)
// return 1 se o sistema autorizar o que o robo pede
// return 0 se o sistema não autorizar
int sistema(int op, Maquina* robo, Dir dir){
    POSICAO nova_pos;
    POSICAO original_pos;
    int force = op*10;
    switch(dir) {
        case Leste:
            nova_pos.i = robo->pos.i;
            nova_pos.j = robo->pos.j + 1;
            break;
        case Oeste:
            nova_pos.i = robo->pos.i;
            nova_pos.j = robo->pos.j - 1;
            break;
        case Nordeste:
            if(robo->pos.i % 2 == 0){
                nova_pos.i = robo->pos.i - 1;
                nova_pos.j = robo->pos.j;
            }
            else{
                nova_pos.i = robo->pos.i - 1;
                nova_pos.j = robo->pos.j + 1;
            }
            break;
        case Sudoeste:
            if(robo->pos.i % 2 == 1){
                nova_pos.i = robo->pos.i + 1;
                nova_pos.j = robo->pos.j;
            }
            else{
                nova_pos.i = robo->pos.i + 1;
                nova_pos.j = robo->pos.j - 1;
            }
            break;
        case Sudeste:
            if(robo->pos.i % 2 == 0){
                nova_pos.i = robo->pos.i + 1;
                nova_pos.j = robo->pos.j;
            }
            else{
                nova_pos.i = robo->pos.i + 1;
                nova_pos.j = robo->pos.j + 1;
            }
            break;
        case Noroeste:
            if(robo->pos.i % 2 == 1){
                nova_pos.i = robo->pos.i - 1;
                nova_pos.j = robo->pos.j;
            }
            else{
                nova_pos.i = robo->pos.i - 1;
                nova_pos.j = robo->pos.j - 1;
            }
            break;
    }

    // checar se o robô não está penalizado
    if(robo->counter != 0){
        printf("Robô não pode se mover. Contador = %d\n", robo->counter);
    }

    switch(op){
        case 1:
            // Verifica se é possível o robô se mover
            // se for possível, atualiza a posição do robô na arena
            // e na interface gráfica
            if( (hex[nova_pos.i][nova_pos.j].ocup) == 0  && nova_pos.i >= 0 && nova_pos.j >= 0){
                original_pos.i = robo->pos.i;
                original_pos.j = robo->pos.j;
                robo->pos.i = nova_pos.i;
                robo->pos.j = nova_pos.j;
                printf("Robo %d indo de %d %d para %d %d\n", robo->reg, original_pos.i, original_pos.j, nova_pos.i, nova_pos.j);
                fprintf(display, "%d %d %d %d %d %d\n",
                                  robo->reg, original_pos.i, original_pos.j, nova_pos.i, nova_pos.j, robo->hp);
                fflush(display);

                if(hex[original_pos.i][original_pos.j].cristais > 0){
                    fprintf(display, "cristal %d %d %d\n", original_pos.i, original_pos.j, hex[original_pos.i][original_pos.j].cristais);
                    fflush(display);
                }

                robo->counter = hex[nova_pos.i][nova_pos.j].terreno-1;

                //Desocupar a célula que o robo saiu e ocupar a célula para qual o robo se moveu.
                hex[original_pos.i][original_pos.j].ocup = 0;
                hex[nova_pos.i][nova_pos.j].ocup = 1;
                return 1;
            }
            else{
                printf("Célula de destino ocupada ou inválida  %d   %d.\n", nova_pos.i, nova_pos.j);
                return 0;
            }
            break;
        case 2:
            if( (hex[nova_pos.i][nova_pos.j].cristais) > 0 && nova_pos.i >= 0 && nova_pos.j >= 0){
                //Adiciona aos cristais carregados pelo robo o número de cristais presentes na célula alvo.
                robo->cristais += hex[nova_pos.i][nova_pos.j].cristais;
                printf("Robô %d recolheu %d cristais\n", robo->reg, hex[nova_pos.i][nova_pos.j].cristais);
                hex[nova_pos.i][nova_pos.j].cristais = 0;

                //Atualiza os cristais da célula alvo na interface gráfica.
                fprintf(display, "erase %d %d\n", nova_pos.i, nova_pos.j);
                fflush(display);

            }
            else {
                printf("Célula sem cristais.\n");
                return 0;
            }
            break;
        case 3:
            if(hex[nova_pos.i][nova_pos.j].ocup == 0 && nova_pos.i >= 0 && nova_pos.j >= 0){
                hex[nova_pos.i][nova_pos.j].cristais += robo->cristais;
                printf("Robô %d depositou %d cristais em %d %d\n", robo->reg, robo->cristais, nova_pos.i, nova_pos.j);
                robo->cristais = 0;

                //Atualiza o número de cristais na célula alvo na interface gráfica.
                fprintf(display, "erase %d %d\n", nova_pos.i, nova_pos.j);
                fprintf(display, "cristal %d %d %d\n", nova_pos.i, nova_pos.j, hex[nova_pos.i][nova_pos.j].cristais);
                fflush(display);
                return 1;

                break;
            }
            else
                return 0;
            break;
        case 4:
            if( (hex[nova_pos.i][nova_pos.j].ocup) == 1 && nova_pos.i >= 0 && nova_pos.j >= 0){
                if(hex[nova_pos.i][nova_pos.j].is_base != 0) printf("Tentativa de ataque em uma base\n");
                else{
                    for(int i=0;i<2*NUMROBOS;i++){
                        if( (rob[i]->pos.i == nova_pos.i) && (rob[i]->pos.j == nova_pos.j)){
                            rob[i]->hp -= 10;
                            k = i;
                            fprintf(display, "%d %d %d %d %d %d\n", rob[i]->reg, nova_pos.i, nova_pos.j, nova_pos.i, nova_pos.j, rob[i]->hp);
                            break;
                        }
                    }
                }
                printf("Robô %d atacou a célula %d %d e acertou o robô %d. HP do robô atacado: %d\n", robo->reg, nova_pos.i, nova_pos.j, k ,rob[k]->hp);
            }
            else
                printf("Tentativa de ataque em uma célula sem robô.\n");
            return 1;
        break;
    }
    return 1;
}
