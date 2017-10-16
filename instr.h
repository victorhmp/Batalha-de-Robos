/* Códigos das instruções */
typedef enum {
    PUSH,
    POP,
    DUP,
    ADD,
    SUB,
    MUL,
    DIV,
    JMP,
    JIT,
    JIF,
    CALL,
    RET,
    EQ,
    GT,
    GE,
    LT,
    LE,
    NE,
    STO,
    RCL,
    END,
    PRN,
    STL,
    RCE,
    SAVE,
    ALC,
    FRE,
    ATR,
    SIS
} OpCode;

/* Tipos dos operandos */
typedef enum {
    NUM,
    ACAO,
    VAR,
    CEL, // celula
} Tipo;

typedef struct{
    // 1 = terreno plano 3 = terreno rugoso
    int terreno;
    // numero de cristais
    int cristais;
    int ocup;
    // 0 = não base / 1 = base time 1 / 2 = base time 2
    int is_base;
    //int team;
} Celula;

/* Operando */


typedef struct {
    // indicador do tipo
    Tipo t;
    union { // atributos (3)
        int n;
        int ac;
        int v;
        Celula c;
    } val;
} OPERANDO;


//typedef int OPERANDO;

/* Instrução */
typedef struct {
    OpCode instr;
    OPERANDO op;
} INSTR;
