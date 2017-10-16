#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

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
    m->ip.val.n = 0;
    m->rbp.val.n = 0;
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
#define rbp (m->rbp)


void exec_maquina(Maquina *m, int n) {
    int i;
    
    exec->topo = 0;
    for (i = 0; i < n; i++) {
        OpCode   opc = prg[ip.val.n].instr;
        OPERANDO arg = prg[ip.val.n].op;
        
        D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg));
        
        switch (opc) {
                OPERANDO tmp;
                OPERANDO op1;
                OPERANDO op2;
                OPERANDO res;
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
                    res.t = NUM;
                    res.val.n = op1.val.n + op2.val.n;
                    empilha(pil, res);
                }
                break;
            case SUB:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                
                if(op1.t==NUM && op2.t==NUM){
                    res.t = NUM;
                    res.val.n = op1.val.n - op2.val.n;
                    empilha(pil, res);
                }
                break;
            case MUL:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                
                if(op1.t==NUM && op2.t==NUM){
                    res.t = NUM;
                    res.val.n = op1.val.n * op2.val.n;
                    empilha(pil, res);
                }
                break;
            case DIV:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                
                if(op1.t==NUM && op2.t==NUM && op2.val.n != 0){
                    res.t = NUM;
                    res.val.n = op1.val.n / op2.val.n;
                    empilha(pil, res);
                }
                break;
            case JMP:
                if(arg.t == NUM) {
                    ip.val.n = arg.val.n;
                }
                continue;
            case JIT:
                if (arg.t == NUM) {
                    op1 = desempilha(pil);
                    if (op1.val.n != 0) {
                        ip.val.n = arg.val.n;
                    }
                    continue;
                }
                break;
            case JIF:
                if (arg.t == NUM) {
                    op1 = desempilha(pil);
                    if (op1.val.n == 0) {
                        ip.val.n = arg.val.n;
                    }
                    continue;
                }
                break;
            case CALL:
                empilha(exec, rbp);
                empilha(exec, ip);
                if (rbp.t == NUM) {
                    rbp.val.n = exec->topo - 1;
                    if(arg.t==NUM)
                        ip.val.n = arg.val.n;
                }
                continue;
            case RET:
                ip = desempilha(exec);
                rbp = desempilha(exec);
                break;
            case EQ:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                
                if (op1.t == NUM && op2.t == NUM) {
                    res.t = NUM;
                    if (op1.val.n == op2.val.n) {
                        res.val.n = 1;
                        empilha(pil, res);
                    }
                    else {
                        res.val.n = 0;
                        empilha(pil, res);
                    }
                }
                break;
            case GT:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                
                if (op1.t == NUM && op2.t == NUM) {
                    res.t = NUM;
                    if (op1.val.n < op2.val.n) {
                        res.val.n = 1;
                        empilha(pil, res);
                    }
                    else {
                        res.val.n = 0;
                        empilha(pil, res);
                    }
                }
                break;
            case GE:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                
                if (op1.t == NUM && op2.t == NUM) {
                    res.t = NUM;
                    if (op1.val.n <= op2.val.n) {
                        res.val.n = 1;
                        empilha(pil, res);
                    }
                    else {
                        res.val.n = 0;
                        empilha(pil, res);
                    }
                }
                break;
            case LT:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                
                if (op1.t == NUM && op2.t == NUM) {
                    res.t = NUM;
                    if (op1.val.n > op2.val.n) {
                        res.val.n = 1;
                        empilha(pil, res);
                    }
                    else {
                        res.val.n = 0;
                        empilha(pil, res);
                    }
                }
                break;
            case LE:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                
                if (op1.t == NUM && op2.t == NUM) {
                    res.t = NUM;
                    if (op1.val.n >= op2.val.n) {
                        res.val.n = 1;
                        empilha(pil, res);
                    }
                    else {
                        res.val.n = 0;
                        empilha(pil, res);
                    }
                }
                break;
            case NE:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                
                if (op1.t == NUM && op2.t == NUM) {
                    res.t = NUM;
                    if (op1.val.n != op2.val.n) {
                        res.val.n = 1;
                        empilha(pil, res);
                    }
                    else {
                        res.val.n = 0;
                        empilha(pil, res);
                    }
                }
                break;
            case STO:
                if (arg.t == NUM) {
                    m->Mem[arg.val.n] = desempilha(pil);
                }
                break;
            case RCL:
                if (arg.t == NUM) {
                    empilha(pil,m->Mem[arg.val.n]);
                }
                break;
            case END:
                return;
            case PRN:
                printf("%d\n", desempilha(pil));
                break;
            case STL: // store local
                if (arg.t == NUM && rbp.t == NUM) {
                    exec->val[arg.val.n+ rbp.val.n] = desempilha(pil);
                }
                break;
            case RCE: // restore local
                if (arg.t == NUM && rbp.t == NUM) {
                    empilha(pil, exec->val[arg.val.n+ rbp.val.n]);
                }
                break;
            case SAVE:
                break;
            case ALC:
                exec->topo += arg.val.n;
                break;
            case FRE:
                exec->topo -= arg.val.n;
                break;
            case ATR:
                op1 = desempilha(pil);
                if (op1.t == CEL && arg.t == NUM) {
                    res.t = NUM;
                    
                    if (arg.val.n == 0)
                        res.val.n = op1.val.c.terreno;
                    if (arg.val.n == 1)
                        res.val.n = op1.val.c.cristais;
                    if (arg.val.n == 2)
                        res.val.n = op1.val.c.ocup;
                    if (arg.val.n == 3)
                        res.val.n = op1.val.c.is_base;
                }
                empilha(pil, res);
                // get object atribute
                break;
                case SIS:
                    // chama o sistema
                    break;
                }
                D(imprime(pil,5));
                D(imprime(exec,20));
                D(puts("\n"));
                
                ip.val.n++;
        }
    }
