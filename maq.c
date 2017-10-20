#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

// função para debug
// #define DEBUG

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
	"ATR",
	"SIS"
};
char *TYPE[] = {
	"NUM",
	"ACAO",
	"VAR",
	"CEL"
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

// função que faz o robô (maquina) executar um número n de instruções
void exec_maquina(Maquina *m, int n) {
	int i;

  // garantia de que o topo é inicializado em 0
  // problemas observados, sem essa linha, no MacOS
	exec->topo = 0;

	for (i = 0; i < n; i++) {
		OpCode   opc = prg[ip].instr;
		OPERANDO arg = prg[ip].op;

		// OPERANDO possui tipos de dados diferentes
		// instruções devem ser passadas na forma INSTR TIPO ARG
		// exemplo: {PUSH NUM 8}

		// imprime no modo DEBUG:
		//  posição do IP, código da instrução, tipo do argumento e valor do argumento
		D(printf("%3d: %-4.4s  %-4.4s %d\n     ", ip, CODES[opc], TYPE[arg.t], arg.val.n));

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
					resp.t = NUM;
					resp.val.n = op1.val.n + op2.val.n;
					empilha(pil, resp);
				}
				break;
			case SUB:
				op1 = desempilha(pil);
				op2 = desempilha(pil);

				if(op1.t==NUM && op2.t==NUM){
					resp.t = NUM;
					resp.val.n = op2.val.n - op1.val.n;
					empilha(pil, resp);
				}
				break;
			case MUL:
				op1 = desempilha(pil);
				op2 = desempilha(pil);

				if(op1.t==NUM && op2.t==NUM){
					resp.t = NUM;
					resp.val.n = op1.val.n * op2.val.n;
					empilha(pil, resp);
				}
				break;
			case DIV:
				op1 = desempilha(pil);
				op2 = desempilha(pil);

				if(op1.t==NUM && op2.t==NUM && op2.val.n != 0){
					resp.t = NUM;
					resp.val.n = op1.val.n / op2.val.n;
					empilha(pil, resp);
				}
				break;
			case JMP:
				if(arg.t == NUM) {
					ip = arg.val.n;
					continue;
				}
			case JIT:
				if (arg.t == NUM) {
					op1 = desempilha(pil);
					if (op1.val.n != 0) {
						ip = arg.val.n;
						continue;
					}
				}
				break;
			case JIF:
				if (arg.t == NUM) {
					op1 = desempilha(pil);
					if (op1.val.n == 0) {
						ip = arg.val.n;
						continue;
					}
				}
				break;
			case CALL:
				op1.t = NUM;
				op1.val.n = m->rbp;
				empilha(exec, op1);
				op2.t = NUM;
				op2.val.n = ip;
				empilha(exec, op2);
				m->rbp = exec->topo - 1;
				if(arg.t==NUM)
					ip = arg.val.n;
				continue;
			case RET:
				op1 = desempilha(exec);
				if(op1.t == NUM)
					ip = op1.val.n; 
				op2 = desempilha(exec);
				if(op2.t==NUM)
					m->rbp = op2.val.n;
				break;
			case EQ:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				resp.t = NUM;
				if( op1.val.n == op2.val.n){
					resp.val.n = 1;
					empilha(pil, resp);
				}
				else{
					resp.val.n = 0;
					empilha(pil, resp);
				}
				break;
			case GT:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				resp.t = NUM;
				if(op1.t==NUM && op2.t==NUM && op1.val.n < op2.val.n){
					resp.val.n = 1;
					empilha(pil, resp);
				}
				else{
					resp.val.n = 0;
					empilha(pil, resp);
				}
				break;
			case GE:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				resp.t = NUM;
				if(op1.t==NUM && op2.t==NUM && op1.val.n <= op2.val.n){
					resp.val.n = 1;
					empilha(pil, resp);
				}
				else{
					resp.val.n = 0;
					empilha(pil, resp);
				}
				break;
			case LT:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				resp.t = NUM;
				if(op1.t==NUM && op2.t==NUM && op1.val.n > op2.val.n){
					resp.val.n = 1;
					empilha(pil, resp);
				}
				else{
					resp.val.n = 0;
					empilha(pil, resp);
				}
				break;
			case LE:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				resp.t = NUM;
				if(op1.t==NUM && op2.t==NUM && op1.val.n >= op2.val.n){
					resp.val.n = 1;
					empilha(pil, resp);
				}
				else{
					resp.val.n = 0;
					empilha(pil, resp);
				}
				break;
			case NE:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				resp.t = NUM;
				if(op1.t==NUM && op2.t==NUM && op1.val.n != op2.val.n){
					resp.val.n = 1;
					empilha(pil, resp);
				}
				else{
					resp.val.n = 0;
					empilha(pil, resp);
				}
				break;
			case STO:
				if(arg.t==NUM){
					m->Mem[arg.val.n] = desempilha(pil);
				}
				break;
			case RCL:
				if(arg.t==NUM){
					empilha(pil,m->Mem[arg.val.n]);
				}
				break;
			case END:
				return;
			case PRN:
				op1 = desempilha(pil);
				printf("%d\n", op1.val.n);
				break;
			case STL: // store local
				if(arg.t==NUM){
					op1 = desempilha(pil);
					exec->val[arg.val.n + m->rbp] = op1;
				}
				break;
			case RCE: // restore local
				if(arg.t==NUM){
					empilha(pil, exec->val[arg.val.n + m->rbp]);
				}
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
				op1 = desempilha(pil);
				if(op1.t == CEL && arg.t == NUM){
					resp.t = NUM;
					if (arg.val.n == 0)
						resp.val.n = op1.val.c.terreno;
					if (arg.val.n == 1)
						resp.val.n = op1.val.c.cristais;
					if (arg.val.n == 2)
						resp.val.n = op1.val.c.ocup;
					if (arg.val.n == 3)
						resp.val.n = op1.val.c.is_base;

					empilha(pil, resp);
				}
				break;
			case SIS:
				if(arg.t == ACAO){
					switch(arg.val.acao.c){
						int ok = 0;
						case MOVE:
							if(sistema(1, *m, arg)) ok = 1;
							break;
						case RECOLHE:
							if(sistema(2, *m, arg)) ok = 1;
							break;
						case DEPOSITA:
							if(sistema(3, *m, arg)) ok = 1;
							break;
						case TIPOATAQUE:
							if(sistema(4, *m, arg)) ok = 1;
							break;
					}
				}
				break;
		}
		D(imprime(pil,5));
		D(imprime(exec,20));
		D(puts("\n"));

		ip++;
	}
}
