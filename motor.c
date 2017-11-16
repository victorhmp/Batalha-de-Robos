/* teste para as instruções implementadas na segunda fase. Quando
 houver operando, é necessário que a instrução especifique o seu tipo.
 Exemplo: {PUSH, NUM, 8}. Nas chamadas ao sistema, primeiro se deve
 inserir uma instrução {PUSH, DIR, direcao} e, depois, a instrução
 {SIS, ACAO, nome da acao}. Exemplo: {PUSH, DIR, SUL},
 {SIS, ACAO, MOVE}
 */

#include<stdio.h>
#include"arena.h"

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


INSTR rob0 [] = {
    {PUSH, DIR, NOD},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOR},
    {SIS, ACAO, MOVE},
    {END}
};

INSTR rob1 [] = {
    {PUSH, DIR, NOR},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOR},
    {SIS, ACAO, RECOLHE},
    {END}
};

INSTR rob2 [] = {
    {PUSH, DIR, NOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SUD},
    {SIS, ACAO, MOVE},
    {END}
};

INSTR rob3 [] = {
    {END}
};

INSTR rob4 [] = {
    {PUSH, DIR, NOD},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOR},
    {SIS, ACAO, TIPOATAQUE},
    {END}
};

INSTR rob5 [] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, RECOLHE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOD},
    {SIS, ACAO, DEPOSITA},
    {END}
};

INSTR rob6 [] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {END}
};

INSTR rob7 [] = {
    {END}
};

INSTR rob8 [] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, TIPOATAQUE},
    {END}
};

INSTR rob9 [] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, RECOLHE},
    {PUSH, DIR, SUD},
    {SIS, ACAO, DEPOSITA},
    {END}
};


// MAXRO 50
// MAXSIZE 20
// NUMROBOS 5
// CICLOS 100
int main(int ac, char **av) {
    int size = 9;
    cria_arena(size);
    
    insere_exercito(size, rob0, rob1, rob2, rob3, rob4, 1);
    insere_exercito(size, rob5, rob6, rob7, rob8, rob9, 2);
    
    printf("Posição dos robôs (original): %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d\n",
           arena->robo[0]->pos.i, arena->robo[0]->pos.j, arena->robo[1]->pos.i, arena->robo[1]->pos.j, arena->robo[2]->pos.i, arena->robo[2]->pos.j, arena->robo[3]->pos.i, arena->robo[3]->pos.j, arena->robo[4]->pos.i, arena->robo[4]->pos.j, arena->robo[5]->pos.i, arena->robo[5]->pos.j, arena->robo[6]->pos.i, arena->robo[6]->pos.j, arena->robo[7]->pos.i, arena->robo[7]->pos.j, arena->robo[8]->pos.i, arena->robo[8]->pos.j, arena->robo[9]->pos.i, arena->robo[9]->pos.j);
    
    atualiza();
    
    printf("Posição dos robôs: %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d\n",
           arena->robo[0]->pos.i, arena->robo[0]->pos.j, arena->robo[1]->pos.i, arena->robo[1]->pos.j, arena->robo[2]->pos.i, arena->robo[2]->pos.j, arena->robo[3]->pos.i, arena->robo[3]->pos.j, arena->robo[4]->pos.i, arena->robo[4]->pos.j, arena->robo[5]->pos.i, arena->robo[5]->pos.j, arena->robo[6]->pos.i, arena->robo[6]->pos.j, arena->robo[7]->pos.i, arena->robo[7]->pos.j, arena->robo[8]->pos.i, arena->robo[8]->pos.j, arena->robo[9]->pos.i, arena->robo[9]->pos.j);
    
    puts("---");
    
    return 0;
}
