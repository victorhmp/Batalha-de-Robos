#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

 #define DEBUG

#ifdef DEBUG
#  define D(X) X
char *CODES[] = {
  "PUSH",
  "POP",
  "DUP",
  "ADD",
  "SUB",
  "MUL",
  "DIV",
  "JMP",
  "JIT",
  "JIF",
  "CALL",
  "RET",
  "EQ",
  "GT",
  "GE",
  "LT",
  "LE",
  "NE",
  "STO",
  "RCL",
  "END",
  "PRN",
  "STL",
  "RCE",
  "SAVE",
  "ALC",
  "FRE",
  "ATR"
  };
#else
#  define D(X)
#endif

static void Erro(char *msg) {
  fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Maquina *cria_maquina(INSTR *p) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  m->ip = 0;
  m->rbp = 0;
  m->prog = p;
  m->cristais = 0;
  m->hp = 0;
  m->team = 0;
  return m;
}

void destroi_maquina(Maquina *m) {
  free(m);
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)

void exec_maquina(Maquina *m, int n) {
  int i;
  
  exec->topo = 0;
  for (i = 0; i < n; i++) {
	OpCode   opc = prg[ip].instr;
	Tipo ti = prg[ip].t;
	OPERANDO arg = prg[ip].op;

	arg.t = ti;

	//char *c = 

	D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg.val.n));

	switch (opc) {
	  OPERANDO tmp;
	  OPERANDO op1;
	  OPERANDO op2;
	  OPERANDO resp;
	case PUSH:
	  empilha(pil, arg);
	  break;
	case POP:
	  desempilha(pil);
	  break;
	case DUP:
	  tmp = desempilha(pil);
	  empilha(pil, tmp);
	  empilha(pil, tmp);
	  break;
	case ADD:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if(op1.t==NUM && op2.t==NUM){
	  	resp.val.n = op1.val.n + op2.val.n;
	  	empilha(pil, resp);
	  }
	  break;
	case SUB:
	  tmp = desempilha(pil);
	  op2 = desempilha(pil);
	  if(op2.t==NUM && tmp.t==NUM){
	  	resp.val.n = op2.val.n - tmp.val.n;
	  	empilha(pil, resp);
	  }
	  break;
	case MUL:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if(op1.t==NUM && op2.t==NUM){
	  	resp.val.n = op1.val.n * op2.val.n;
	  	empilha(pil, resp);
	  }
	  break;
	case DIV:
	  tmp = desempilha(pil);
	  op1 = desempilha(pil);
	  if(op1.t==NUM && op2.t==NUM && tmp.val.n!=0){
	  	resp.val.n = op1.val.n / tmp.val.n;
	  	empilha(pil, resp);
	  }
	  break;
	case JMP:
	  ip = arg.val.n;
	  continue;
	case JIT:
	  op1 = desempilha(pil);
	  if (op1.val.n != 0) {
		ip = arg.val.n;
		continue;
	  }
	  break;
	case JIF:
	  op1 = desempilha(pil);
	  if (op1.val.n == 0) {
		ip = arg.val.n;
		continue;
	  }
	  break;
	case CALL:
		if(arg.t==NUM){
			op1.t = NUM;
			op1.val.n = m->rbp;
			op2.t = NUM;
			op2.val.n = ip;
			//empilha(exec, m->rbp);
		  	//empilha(exec, ip);
		  	empilha(exec, op1);
		  	empilha(exec, op2);
		  	m->rbp = exec->topo - 1;
		  	ip = arg.val.n;
		}
	  continue;
	case RET:
	  op1 = desempilha(exec);
	  ip = op1.val.n;
	  op2 = desempilha(exec);
	  m->rbp = op2.val.n;
	  break;
	case EQ:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t==NUM && op2.t==NUM && op1.val.n == op2.val.n){
	  	resp.t = NUM;
	  	resp.val.n = 1;
	  	empilha(pil, resp);
	  }
	  else{
	  	resp.t = NUM;
	  	resp.val.n = 0;
	  	empilha(pil, resp);
	  }
	  break;
	case GT:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t==NUM && op2.t==NUM && op1.val.n < op2.val.n){
	  	resp.t = NUM;
	  	resp.val.n = 1;
	  	empilha(pil, resp);
	  }
	  else{
	  	resp.t = NUM;
	  	resp.val.n = 0;
	  	empilha(pil, resp);
	  }
	  break;
	case GE:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t==NUM && op2.t==NUM && op1.val.n <= op2.val.n){
	  	resp.t = NUM;
	  	resp.val.n = 1;
	  	empilha(pil, resp);
	  }
	  else{
	  	resp.t = NUM;
	  	resp.val.n = 0;
	  	empilha(pil, resp);
	  }
	  break;
	case LT:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t==NUM && op2.t==NUM && op1.val.n > op2.val.n){
	  	resp.t = NUM;
	  	resp.val.n = 1;
	  	empilha(pil, resp);
	  }
	  else{
	  	resp.t = NUM;
	  	resp.val.n = 0;
	  	empilha(pil, resp);
	  }
	  break;
	case LE:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t==NUM && op2.t==NUM && op1.val.n >= op2.val.n){
	  	resp.t = NUM;
	  	resp.val.n = 1;
	  	empilha(pil, resp);
	  }
	  else{
	  	resp.t = NUM;
	  	resp.val.n = 0;
	  	empilha(pil, resp);
	  }
	  break;
	case NE:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t==NUM && op2.t==NUM && op1.val.n != op2.val.n){
	  	resp.t = NUM;
	  	resp.val.n = 1;
	  	empilha(pil, resp);
	  }
	  else{
	  	resp.t = NUM;
	  	resp.val.n = 0;
	  	empilha(pil, resp);
	  }
	  break;
	case STO:
	  if(arg.t==NUM){
	  	m->Mem[arg.val.n] = desempilha(pil);
	  }
	  //m->Mem[arg] = desempilha(pil);
	  break;
	case RCL:
	  if(arg.t==NUM){
	  	empilha(pil, m->Mem[arg.val.n]);
	  }
	  //empilha(pil,m->Mem[arg]);
	  break;
	case END:
	  return;
	case PRN:
	  resp = desempilha(pil);
	  if(resp.t==NUM){
	  	printf("%d\n", resp.val.n);
	  }
	  break;
	case STL: // store local
		op1 = desempilha(pil);
		if(arg.t==NUM){
			exec->val[arg.val.n + m->rbp] = op1;
		}
		//exec->val[arg + m->rbp] = desempilha(pil);
		break;
	case RCE: // restore local
		op1 = desempilha(pil);
		if(arg.t==NUM){
			resp = exec->val[arg.val.n + m->rbp];
		}
		//empilha(pil, exec->val[arg+ m->rbp]);
		break;
	case SAVE:
		break;
	case ALC:
		if(arg.t==NUM){
			exec->topo += arg.val.n;
		}
		break;
	case FRE:
		if(arg.t==NUM){
			exec->topo -= arg.val.n;
		}
		break;
	case ATR:
		// get object atribute
		break;
	}
	D(imprime(pil,5));
	D(imprime(exec,20));
	D(puts("\n"));

	ip++;
  }
}
