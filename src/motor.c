#include <stdio.h>
#include "arena.h"

#define SIZE 12


int main(int ac, char **av) {
    
    /* para fazer os testes, comente a linha acima e descomente a relativa ao teste desejado
     lembre-se de que a saída de cada teste será dada 10 vezes (uma para cada robô) */
    
    //FILE *p = fopen("fat", "r");
    //FILE *p = fopen("fatorial", "r");
    //FILE *p = fopen("fat", "r");
    //FILE *p = fopen("errado", "r");
    //FILE *p = fopen("exemplo", "r");
    //FILE *p = fopen("função", "r");
    //FILE *p = fopen("função2", "r");
    
    display = popen("./apres", "w");
    
    if (display == NULL) {
        fprintf(stderr,"Não encontrei o programa de exibição\n");
        return 1;
    }
    
    cria_arena(SIZE);
    
    int length = 0;
    
    insere_exercito(SIZE, 1);
    insere_exercito(SIZE, 2);
    
    atualiza(50);
    puts("---");
    fprintf(display, "fim\n");
    pclose(display);
    return 0;
    
}
