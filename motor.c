/* teste para as instruções implementadas na segunda fase. Quando
 houver operando, é necessário que a instrução especifique o seu tipo.
 Exemplo: {PUSH, NUM, 8}. Nas chamadas ao sistema, primeiro se deve
 inserir uma instrução {PUSH, DIR, direcao} e, depois, a instrução
 {SIS, ACAO, nome da acao}. Exemplo: {PUSH, DIR, SUL},
 {SIS, ACAO, MOVE}
*/

#include<stdio.h>
#include "maq.h" 

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
INSTR rob1[] = {
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

int main(int ac, char **av) { 
  cria_arena(15);

  // posição dos robôs
  POSICAO r1 = {5, 2};
  POSICAO r2 = {1, 3};
  POSICAO robos[1] = {r1};
  POSICAO robos2[1] = {r2};

  insere_exercito(1, robos, fat);
  insere_exercito(2, robos2, fat);

  //atualiza();

  //Maquina *maq = cria_maquina(rob2);
  //exec_maquina(maq, 1000); 
  puts("---"); 
  //destroi_maquina(maq); 

  return 0; 
}
