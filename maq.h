#include "pilha.h"

#define MAXMEM 100

typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip; // instru pointer
  int rbp; // base register

  // new robot atributes
  int cristals;
  int hp;
  // position in the grid(i,j)
  int i;
  int j;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);
