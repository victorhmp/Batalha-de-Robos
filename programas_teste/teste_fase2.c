#include<stdio.h>
#include "arena.h"

/* teste para as instruções implementadas na segunda fase. Quando
 houver operando, é necessário que a instrução especifique o seu tipo.
 Exemplo: {PUSH, NUM, 8}. Nas chamadas ao sistema, primeiro se deve
 inserir uma instrução {PUSH, DIR, direcao} e, depois, a instrução
 {SIS, ACAO, nome da acao}. Exemplo: {PUSH, DIR, SUL},
 {SIS, ACAO, MOVE}
*/

// Teste para 2 robôs (apenas um time), 1 cristal e 1 base


 // robô recolhe um cristal, se movimenta e o deposita novamente
INSTR new1[] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, RECOLHE},
    {PUSH, DIR, NOE},
    {SIS, ACAO, MOVE},
    {PUSH, DIR, SUL},
    {SIS, ACAO, DEPOSITA},
    {END, NUM, 0}
};

// robô tenta atacar
INSTR new2 [] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, TIPOATAQUE},
    {END, NUM, 0}
};

int main(int ac, char **av) {
    
    // posições
    POSICAO b0 = {0, 0}; //base
    POSICAO b[1] = {b0};
    
    POSICAO c0 = {3, 3}; //cristal
    POSICAO c[1] = {c0};
    int n[1] = {1}; // apenas um cristal na posição de c
    
    POSICAO terreno0 = {5, 0}; // terreno rugoso
    POSICAO terreno[1] = {terreno0};
    
    POSICAO r1 = {5, 2}; //robôs
    POSICAO r2 = {1, 3};
    POSICAO robos[2] = {r1, r2};
    
    
    // arena criada
    cria_arena(9, b, c, n, terreno, new1, new2);
    // exército inserido
    //insere_exercito(0, robos);
    
    return 0;
}

