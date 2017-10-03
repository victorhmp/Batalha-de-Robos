/***********************

Prototipo da arena

***********************/
typedef struct{
	int robots[];
	int time;
} Arena;

typedef struct{
	Tipo terreno;
	int cristals;
	int ocup;
	int is_base;
} Celula;

typedef struct{
	// position
	int i;
	int j;
} ROBOT;
