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
  ATR
} OpCode;

/* Tipos dos operandos */
typedef enum {
  NUM,
  ACAO,
  VAR,
  CEL
} Tipo;

/* Operando */
typedef struct { 
    // indicador do tipo
    Tipo t; 
    union { // atributos (3)
   	  int n; 
   	  int ac; 
   	  int v; 
    }; 
} OPERANDO;

// typedef int OPERANDO;

/* Instrução */
typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;
