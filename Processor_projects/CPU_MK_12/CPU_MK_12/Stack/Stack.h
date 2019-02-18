#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double elem_t;
const int signal = 0xBEDABEDA;
const int INITIAL_STACK_CAPACITY = 10;
const int POISON = -666;
const int STACK_OK = 0;
const elem_t CANARY = 42.42;

struct Stack {
	int canary1;
	int size;
	elem_t * data;
	int capacity;
	int canary2;
};

struct Stack * init_stack();

int StackPush(struct Stack * stc, elem_t val);

struct Stack * init_stack();

elem_t StackPop(struct Stack * stc);

int IncreaseStack(struct Stack * stc);

int StackDump(struct Stack * stc);

int StackOk(struct Stack * stc);

int StackDestruct(struct Stack * stc);