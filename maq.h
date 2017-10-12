#include "pilha.h"

#define MAXMEM 100

typedef struct{
  int i;
  int j;
} POSICAO;

typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip; // instru pointer
  int rbp; // base register

  // atributos do robo
  int cristais;
  int hp;

  // posição na grid
  POSICAO pos;

  // time do robo
  // team = 1 || team = 2
  // team == 0 -> robo sem time
  // (não inserido ainda ou inativo)
  int team;
} Maquina;



Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);



