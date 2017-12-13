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
    /*STL,
    RCE,
    ALC,
    FRE,
	*/
    ATR,
    SIS,
	ENTRY,
	LEAVE
} OpCode;

/* Tipos dos operandos */
typedef enum {
    NUM,
    ACAO,
    VAR,
    CEL, // celula
    DIR,
} Tipo;

typedef struct{
    // 1 = terreno plano 3 = terreno rugoso
    // facilmente expansível
    short int terreno;
    // numero de cristais
    short int cristais;
    short int ocup;
    // 0 = não base / 1 = base time 1 / 2 = base time 2
    short int is_base;
} Celula;

//enum Comando são as possíveis ações que o robo executa
typedef enum{
    MOVE,
    RECOLHE,
    DEPOSITA,
    TIPOATAQUE
} Comando;

typedef struct{
    Comando c;
    char *dir;
} Acao;

typedef enum {
    Leste,
    Oeste,
    Nordeste,
    Sudoeste,
    Sudeste,
    Noroeste
} Dir;

typedef struct {
    // indicador do tipo
    Tipo t;
    union { // atributos
        int n;
        int ac;
        int v;
        Celula c;
        Acao acao;
        Dir dir;
    } val;
} OPERANDO;

/* Instrução */
typedef struct {
    OpCode instr;
    OPERANDO op;
} INSTR;
