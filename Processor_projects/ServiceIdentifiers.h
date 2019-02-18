#define MEMORY_SIZE 512
#define LABELS_COUNT 32
#define TOLERANCE 0.000001
const int INITIAL_LINE = 128;

enum Errors {
	MEMORY_ERROR = -20,
	LABEL_ERROR,
	FILE_ERROR,
	DIVISION_ERROR,
	INCORRECT_ARGUMENT,
	EXECUTION_ERROR,
	PTR_ERROR
};

//                         
//--------------------------------
#define CMD_PUSH                1 
#define CMD_PUSH_REG            11
#define CMD_PUSH_RAM            12
#define CMD_PUSH_RAM_REG        13
#define CMD_PUSH_RAM_REG_SUM    14
//--------------------------------
#define CMD_POP                 2
#define CMD_POP_RAM             21
#define CMD_POP_REG             22
#define CMD_POP_RAM_REG         23
#define CMD_POP_RAM_REG_SUM     24
//--------------------------------
#define CMD_SUM                 3
#define CMD_MUL                 4
#define CMD_DIV                 5
#define CMD_SUB                 6
#define CMD_SQRT                7
//--------------------------------
#define CMD_LABEL				8
#define CMD_JMP                 80
#define CMD_JE                  81
#define CMD_JNE                 82
#define CMD_JA                  83
#define CMD_JAE                 84
#define CMD_JB                  85
#define CMD_JBE                 86
//--------------------------------
#define CMD_OUT                 91
#define CMD_IN                  92
#define CMD_NAN                 100
#define CMD_START               101
#define CMD_END                 102
//--------------------------------