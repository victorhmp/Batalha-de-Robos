/* teste para as instruções implementadas na segunda fase. Quando
 houver operando, é necessário que a instrução especifique o seu tipo.
 Exemplo: {PUSH, NUM, 8}. Nas chamadas ao sistema, primeiro se deve
 inserir uma instrução {PUSH, DIR, direcao} e, depois, a instrução
 {SIS, ACAO, nome da acao}. Exemplo: {PUSH, DIR, SUL},
 {SIS, ACAO, MOVE}
 */

#include<stdio.h>
#include"arena.h"

#define SIZE 15

INSTR fat[] = {
    {PUSH, NUM, 8},  // 0
    {CALL, NUM, 4},  // 1
    {PRN,  NUM, 0},  // 2
    {END,  NUM, 0},  // 3
    
    // FAT
    {ALC,  NUM, 1},  // 4
    {DUP,  NUM, 0},  // 5
    {STL,  NUM, 1},  // 6 n
    {PUSH, NUM, 1},  // 7
    {EQ,   NUM, 0},  // 8 n == 1 ?
    {JIF, NUM, 13},  // 9
    {PUSH, NUM, 1},  // 10
    {FRE,  NUM, 1},  // 11
    {RET,  NUM, 0},  // 12
    {RCE,  NUM, 1},  // 13 n
    {PUSH, NUM, 1},  // 14
    {SUB,  NUM, 0},  // 15 n-1
    {CALL, NUM, 4},  // 16 fat(n-1)
    {RCE,  NUM, 1},  // 17 n
    {MUL,  NUM, 0},  // 18 n * fat(n-1)
    {FRE,  NUM, 1},  // 19
    {RET,  NUM, 0}   // 20
};

// robô recolhe um cristal, se movimenta e o deposita novamente
INSTR rob1 [] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SUL},
    {SIS, ACAO, MOVE},
    {END, NUM, 0}
};

// robô tenta atacar
INSTR rob2 [] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, TIPOATAQUE},
    {END, NUM, 0}
};

INSTR new[] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, RECOLHE},
    {END},
};

INSTR teste[] = {
    {END}
};


int main(int ac, char **av) {
    cria_arena(SIZE);
    display = popen("./apres", "w");

    if (display == NULL) {
        fprintf(stderr,"Não encontrei o programa de exibição\n");
        return 1;
    }

    insere_exercito(SIZE, rob1, 1);
    insere_exercito(SIZE, teste, 2);

    fprintf(display, "rob ~/visual/roboA.png\nrob ~/visual/roboB.png\n");
    
    /*
    printf("Posição dos robôs (original): %d %d e %d %d\n",
           arena->robo[0]->pos.i, arena->robo[0]->pos.j, arena->robo[1]->pos.i, arena->robo[1]->pos.j);
    for(int i=0;i<100;i++){
        atualiza();
    }
    */
    
    //printf("Posição dos robôs: %d %d e %d %d\n",
    //     arena->robo[0]->pos.i, arena->robo[0]->pos.j, arena->robo[1]->pos.i, arena->robo[1]->pos.j);
    
    puts("---");
    
    return 0;
}
