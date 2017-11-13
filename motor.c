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

INSTR new[] = {
    {PUSH, DIR, SOE},
    {SIS, ACAO, RECOLHE},
    {END},
};

int main(int ac, char **av) { 

  Maquina *maq = cria_maquina(new);
  exec_maquina(maq, 1000); 
  puts("---"); 
  //exec_maquina(maq, 1000); 

  //puts("---"); 
  destroi_maquina(maq); 

  return 0; 
}
