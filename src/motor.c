#include <stdio.h>
#include "compila.tab.h"
#include "arena.h"

#define SIZE 12

// arrays de instruções - robôs do time 1
INSTR p1[2000];
INSTR p2[2000];
INSTR p3[2000];
INSTR p4[2000];
INSTR p5[2000];

// arrays de instruções - robôs do time 2
INSTR p6[2000];
INSTR p7[2000];
INSTR p8[2000];
INSTR p9[2000];
INSTR p10[2000];

int compilador(FILE *, INSTR *);

int main(int ac, char **av) {

    char program[10][3] = {{"p1"}, {"p2"}, {"p3"}, {"p4"}, {"p5"}, {"p6"}, {"p7"}, {"p8"}, {"p9"}, {"p0"}};
    
    for (int i = 0; i < 10; i++) {
        
        FILE *p = fopen(program[i], "r");
        int res;
        
        switch (i) {
            case 0:
                res = compilador(p, p1);
                if (res) return 1;
                break;
            case 1:
                res = compilador(p, p2);
                if (res) return 1;
                break;
            case 2:
                res = compilador(p, p3);
                if (res) return 1;
                break;
            case 3:
                res = compilador(p, p4);
                if (res) return 1;
                break;
            case 4:
                res = compilador(p, p5);
                if (res) return 1;
                break;
            case 5:
                res = compilador(p, p6);
                if (res) return 1;
                break;
            case 6:
                res = compilador(p, p7);
                if (res) return 1;
                break;
            case 7:
                res = compilador(p, p8);
                if (res) return 1;
                break;
            case 8:
                res = compilador(p, p9);
                if (res) return 1;
                break;
            case 9:
                res = compilador(p, p10);
                if (res) return 1;
                break;
        }
    }
    
    
    display = popen("./apres", "w");
    
    if (display == NULL) {
        fprintf(stderr,"Não encontrei o programa de exibição\n");
        return 1;
    }
    
    cria_arena(SIZE);
    
    insere_exercito(SIZE, p1, p2, p3, p4, p5, 1);
    insere_exercito(SIZE, p6, p7, p8, p9, p10, 2);
    
    atualiza(5);
    puts("---");
    fprintf(display, "fim\n");
    pclose(display);
    return 0;
    
}
