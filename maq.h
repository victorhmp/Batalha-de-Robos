#include "pilha.h"

#define MAXMEM 100

// struct simples para guardar a posição de um robô
// poderia ser implementada com um array de duas posições
// sem evidentes vantagens ou desvantagens
typedef struct{
  int i;
  int j;
} POSICAO;

// Maquina virtual / robô
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

  // inteiro para identificar o robo
  // necessário para visualização
  int reg;
  // determina se o robô pode executar um comando
  // ou está ocupada
  int counter;
} Maquina;



Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);



