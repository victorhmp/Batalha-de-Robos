#include<stdio.h>
#include"arena.h"

#define SIZE 12

// Instruções para 10 robôs, testam todas as funções implementadas

INSTR rob0 [] = {
    {PUSH, DIR, LES},
    {SIS, ACAO, RECOLHE},
    {PUSH, DIR, LES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, DEPOSITA},
    {PUSH, DIR, LES},
    {SIS, ACAO, MOVE},
    {END}
};

INSTR rob1 [] = {
    {PUSH, DIR, NOD},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOD},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOE},
    {SIS, ACAO, MOVE},
    {END}
};

INSTR rob2 [] = {
    {PUSH, DIR, LES},
    {SIS, ACAO, RECOLHE},
    {PUSH, DIR, OES},
    {SIS, ACAO, DEPOSITA},
    {END}
};

INSTR rob3 [] = {
    {PUSH, DIR, LES},
    {SIS, ACAO, RECOLHE},
    {PUSH, DIR, LES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, LES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, LES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, LES},
    {SIS, ACAO, MOVE},
    {END}
};

INSTR rob4 [] = {
    {PUSH, DIR, LES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, LES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, LES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOD},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOD},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOD},
    {SIS, ACAO, MOVE},

    {END}
};

INSTR rob5 [] = {
    {PUSH, DIR, SUD},
    {SIS, ACAO, MOVE},
    {END}
};

INSTR rob6 [] = {
    {PUSH, DIR, OES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, NOE},
    {SIS, ACAO, RECOLHE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, DEPOSITA},
    {END}
};

INSTR rob7 [] = {
    {END}
};

INSTR rob8 [] = {
    {PUSH, DIR, OES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, OES},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, OES},
    {SIS, ACAO, MOVE},
    {END}
};

INSTR rob9 [] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, RECOLHE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, RECOLHE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SOE},
    {SIS, ACAO, TIPOATAQUE},
    {END}
};


int main(int ac, char **av) {
    display = popen("./apres", "w");

    if (display == NULL) {
        fprintf(stderr,"Não encontrei o programa de exibição\n");
        return 1;
    }

    cria_arena(SIZE);

    insere_exercito(SIZE, rob0, rob1, rob2, rob3, rob4, 1);
    insere_exercito(SIZE, rob5, rob6, rob7, rob8, rob9, 2);

    /*
    Imprimir posição original em que os robôs foram inseridos
    printf("Posição dos robôs (original): %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d\n",
           arena->robo[0]->pos.i, arena->robo[0]->pos.j, arena->robo[1]->pos.i, arena->robo[1]->pos.j, arena->robo[2]->pos.i, arena->robo[2]->pos.j, arena->robo[3]->pos.i, arena->robo[3]->pos.j, arena->robo[4]->pos.i, arena->robo[4]->pos.j, arena->robo[5]->pos.i, arena->robo[5]->pos.j, arena->robo[6]->pos.i, arena->robo[6]->pos.j, arena->robo[7]->pos.i, arena->robo[7]->pos.j, arena->robo[8]->pos.i, arena->robo[8]->pos.j, arena->robo[9]->pos.i, arena->robo[9]->pos.j);
    */

    atualiza(5);

    /*
    Imprimir posição dos robôs após executarem suas instruções
    printf("Posição dos robôs: %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d e %d %d\n",
           arena->robo[0]->pos.i, arena->robo[0]->pos.j, arena->robo[1]->pos.i, arena->robo[1]->pos.j, arena->robo[2]->pos.i, arena->robo[2]->pos.j, arena->robo[3]->pos.i, arena->robo[3]->pos.j, arena->robo[4]->pos.i, arena->robo[4]->pos.j, arena->robo[5]->pos.i, arena->robo[5]->pos.j, arena->robo[6]->pos.i, arena->robo[6]->pos.j, arena->robo[7]->pos.i, arena->robo[7]->pos.j, arena->robo[8]->pos.i, arena->robo[8]->pos.j, arena->robo[9]->pos.i, arena->robo[9]->pos.j);

   */

    puts("---");
    fprintf(display, "fim\n");
    pclose(display);

    return 0;
}
