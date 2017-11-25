#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

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
    "ALC",
    "FRE",
    "ATR",
    "SIS",
	"ENTRY",
	"LEAVE"
};
char *TYPE[] = {
    "NUM",
    "ACAO",
    "VAR",
    "CEL",
    "DIR"
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
	m->pil.topo = 0;
	m->ib = 0;
    return m;
}

void destroi_maquina(Maquina *m) {
    free(m);
}

int new_frame(Maquina *m, int n){
	int ibc = m->ib;
	if(ibc < MAXFRM-1){
		m->bp[++m->ib] = n+ibc;
		return m->ib;
	}
	return -1;
}

int del_frame(Maquina *m){
	if(m->ib > 0) return --m->ib;
	return -1;
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
    // problemas observados sem essa linha, no MacOS
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
        
        // implementação das funções do robô
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
            case DUP: // duplica elemento no topo da pilha
                tmp = desempilha(pil);
                empilha(pil, tmp);
                empilha(pil, tmp);
                break;
            case ADD: // soma os dois OPERANDOs no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                // apenas se ambos os OPERANDOs forem do tipo NUM
                if(op1.t==NUM && op2.t==NUM){
                    resp.t = NUM;
                    resp.val.n = op1.val.n + op2.val.n;
                    empilha(pil, resp);
                }
                break;
            case SUB: // subtrai os dois OPERANDOs no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                // apenas se ambos forem do tipo NUM
                if(op1.t==NUM && op2.t==NUM){
                    resp.t = NUM;
                    resp.val.n = op2.val.n - op1.val.n;
                    empilha(pil, resp);
                }
                break;
            case MUL: // multiplica os dois OPERANDOs no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                // apenas se ambos forem do tipo NUM
                if(op1.t==NUM && op2.t==NUM){
                    resp.t = NUM;
                    resp.val.n = op1.val.n * op2.val.n;
                    empilha(pil, resp);
                }
                break;
            case DIV: // empilha o quociente dos dois OPERANDOs no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                // apenas se ambos forem do tipo NUM e op2 é não-nulo
                if(op1.t==NUM && op2.t==NUM && op2.val.n != 0){
                    resp.t = NUM;
                    resp.val.n = op1.val.n / op2.val.n;
                    empilha(pil, resp);
                }
                break;
            case JMP: // JUMP
                if(arg.t == NUM) {
                    ip = arg.val.n;
                    continue;
                }
            case JIT: // JUMP IF TRUE
                if (arg.t == NUM) {
                    op1 = desempilha(pil);
                    // faz o JUMP se o elemento no topo da pilha é 1
                    if (op1.val.n != 0) {
                        ip = arg.val.n;
                        continue;
                    }
                }
                break;
            case JIF: // JUMP IF FALSE
                if (arg.t == NUM) {
                    op1 = desempilha(pil);
                    // faz o JUMP se o elemento no topo da pilha é 0
                    if (op1.val.n == 0) {
                        ip = arg.val.n;
                        continue;
                    }
                }
                break;
            case CALL: // chamada de função
                
                // empilha o valor do RBP na pilha de execução
                op1.t = NUM;
                op1.val.n = m->rbp;
                empilha(exec, op1);
                
                // empilha o valor do IP na pilha de execução
                op2.t = NUM;
                op2.val.n = ip;
                empilha(exec, op2);
                
                // faz o RBP apontar para o topo de exec
                m->rbp = exec->topo - 1;
                
                // se o argumento for válido
                // faz o IP apontar para o começo da função
                if(arg.t==NUM)
                    ip = arg.val.n;
                continue;
            case RET:
                // desempilha o IP
                op1 = desempilha(exec);
                if(op1.t == NUM)
                    ip = op1.val.n;
                
                // desempilha o RBP
                op2 = desempilha(exec);
                if(op2.t==NUM)
                    m->rbp = op2.val.n;
                break;
            case EQ: // compara (igualdade) os dois elementos no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                resp.t = NUM;
                
                // empilha o resultado da comparação (0 = false / 1 = true)
                if( op1.val.n == op2.val.n){
                    resp.val.n = 1;
                    empilha(pil, resp);
                }
                else{
                    resp.val.n = 0;
                    empilha(pil, resp);
                }
                break;
            case GT: // compara (>) os dois elementos no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                resp.t = NUM;
                
                // empilha o resultado da comparação (0 = false / 1 = true)
                if(op1.t==NUM && op2.t==NUM && op1.val.n < op2.val.n){
                    resp.val.n = 1;
                    empilha(pil, resp);
                }
                else{
                    resp.val.n = 0;
                    empilha(pil, resp);
                }
                break;
            case GE: // compara (>=) os dois elementos no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                resp.t = NUM;
                
                // empilha o resultado da comparação (0 = false / 1 = true)
                if(op1.t==NUM && op2.t==NUM && op1.val.n <= op2.val.n){
                    resp.val.n = 1;
                    empilha(pil, resp);
                }
                else{
                    resp.val.n = 0;
                    empilha(pil, resp);
                }
                break;
            case LT: // compara (<) os dois elementos no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                resp.t = NUM;
                
                // empilha o resultado da comparação (0 = false / 1 = true)
                if(op1.t==NUM && op2.t==NUM && op1.val.n > op2.val.n){
                    resp.val.n = 1;
                    empilha(pil, resp);
                }
                else{
                    resp.val.n = 0;
                    empilha(pil, resp);
                }
                break;
            case LE: // compara (<=) os dois elementos no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                resp.t = NUM;
                
                // empilha o resultado da comparação (0 = false / 1 = true)
                if(op1.t==NUM && op2.t==NUM && op1.val.n >= op2.val.n){
                    resp.val.n = 1;
                    empilha(pil, resp);
                }
                else{
                    resp.val.n = 0;
                    empilha(pil, resp);
                }
                break;
            case NE: // compara (!=) os dois elementos no topo da pilha
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                resp.t = NUM;
                
                // empilha o resultado da comparação (0 = false / 1 = true)
                if(op1.t==NUM && op2.t==NUM && op1.val.n != op2.val.n){
                    resp.val.n = 1;
                    empilha(pil, resp);
                }
                else{
                    resp.val.n = 0;
                    empilha(pil, resp);
                }
                break;
            case STO: // salva na memória o elemento no topo da pilha de dados
                if(arg.t==NUM){
                    m->Mem[arg.val.n+m->bp[m->ib]] = desempilha(pil);
                }
                break;
            case RCL: // restaura o STO
                if(arg.t==NUM){
                    empilha(pil,m->Mem[arg.val.n+m->bp[m->ib]]);
                }
                break;
            case END:
				pil->topo = 0;
                return;
            case PRN: // print do valor numérico do OPERANDO no topo da pilha
                op1 = desempilha(pil);
                printf("%d\n", op1.val.n);
                break;
            case STL: // salva na pilha de execução o elemento no topo da pilha de dados
                if(arg.t==NUM){
                    op1 = desempilha(pil);
                    exec->val[arg.val.n + m->rbp] = op1;
                }
                break;
            case RCE: // restaura o STL
                if(arg.t==NUM){
                    empilha(pil, exec->val[arg.val.n + m->rbp]);
                }
                break;
            case ALC: // aloca espaço na pilha de execução
                if(arg.t==NUM){
                    exec->topo += arg.val.n;
                }
                break;
            case FRE: // libera espaço da pilha de execução
                if(arg.t==NUM){
                    exec->topo -= arg.val.n;
                }
                break;
            case ATR: // função especial para checar propriedades de uma célula
                op1 = desempilha(pil);
                
                // se o elemento do topo da pilha for do tipo Celula
                // empilho seu atributo de índice arg
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
                op1 = desempilha(pil);
                if(arg.t == ACAO && op1.t == DIR){
                    switch(arg.val.acao.c){
                            int ok = 0;
                        case MOVE:
                            if(sistema(1, m, op1.val.dir)) ok = 1;
                            break;
                        case RECOLHE:
                            if(sistema(2, m, op1.val.dir)) ok = 1;
                            break;
                        case DEPOSITA:
                            if(sistema(3, m, op1.val.dir)) ok = 1;
                            break;
                        case TIPOATAQUE:
                            if(sistema(4, m, op1.val.dir)) ok = 1;
                            break;
                    }
                }
                break;
			case ENTRY:
				new_frame(m, arg.val.n);
				break;
			case LEAVE:
				del_frame(m);
				break;
        }

        D(imprime(pil,5));
        D(imprime(exec,20));
        D(puts("\n"));
        
        ip++;
    }
}
