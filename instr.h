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
    NUM,  // numero inteiro
    ACAO, // ação
    VAR,  // variável
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

// enum Comando são as possíveis ações que o robo executa
typedef enum{
    MOVE,
    RECOLHE,
    DEPOSITA,
    TIPOATAQUE
} Comando;

// Acao faz parte de chamadas do comando SIS
// simplesmente diz qual ação estamos tentando executar
// e sua direção
typedef struct{
    Comando c;
    char *dir;
} Acao;


typedef struct {
    // indicador do tipo
    Tipo t;
    union { // possíveis valores para o par {Tipo, Valor}
        int n;
        int ac;
        int v;
        Celula c;
        Acao aca;
    } val;
} OPERANDO;

/* Instrução */
typedef struct {
    OpCode instr;
    OPERANDO op;
} INSTR;
