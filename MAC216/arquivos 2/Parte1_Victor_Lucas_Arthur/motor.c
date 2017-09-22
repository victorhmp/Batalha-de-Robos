#include<stdio.h>
#include "maq.h" 

INSTR fat[] = {
    {PUSH, 8},  // 0
    {CALL, 4},  // 1
    {PRN,  0},  // 2
    {END,  0},  // 3

    // FAT
    {ALC,  1},  // 4
    {DUP,  0},  // 5
    {STL,  1},  // 6 n
    {PUSH, 1},  // 7
    {EQ,   0},  // 8 n == 1 ?
    {JIF, 13},  // 9
    {PUSH, 1},  // 10
    {FRE,  1},  // 11
    {RET,  0},  // 12
    {RCE,  1},  // 13 n
    {PUSH, 1},  // 14
    {SUB,  0},  // 15 n-1
    {CALL, 4},  // 16 fat(n-1)
    {RCE,  1},  // 17 n
    {MUL,  0},  // 18 n * fat(n-1)
    {FRE,  1},  // 19
    {RET,  0}   // 20
};

int main(int ac, char **av) { 

  Maquina *maq = cria_maquina(fat);
  //printf("%d\n", &exec->topo);
  exec_maquina(maq, 1000); 
  puts("---"); 
  //exec_maquina(maq, 1000); 

  //puts("---"); 
  destroi_maquina(maq); 

  return 0; 
}
