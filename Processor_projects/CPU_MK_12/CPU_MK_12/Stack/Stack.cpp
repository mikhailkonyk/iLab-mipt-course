#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Stack.h"

/**
	@brief creates a stack, allocates memory, and initializes variables.
*/

struct Stack * init_stack() {
	struct Stack * stc = (Stack *)calloc(1, sizeof(struct Stack));
	if (stc == NULL) {
		printf(" Stack is not created\n");
		return NULL;
	}
	stc->canary1 = signal;
	stc->canary2 = signal;
	stc->size = 2;
	stc->data = (elem_t *)calloc(INITIAL_STACK_CAPACITY, sizeof(elem_t));
	elem_t * tmp = stc->data;
	tmp[0] = CANARY;
	tmp[stc->size - 1] = CANARY;
	for (int i = 1; i < INITIAL_STACK_CAPACITY; i++)
		tmp[i] = POISON;
	stc->capacity = INITIAL_STACK_CAPACITY;

	return stc;
}

/**
	@brief frees up stack memory
*/

int StackDestruct(struct Stack * stc) {
	if (StackOk(stc) == STACK_OK) {
		free(stc->data);
		free(stc);
		return 0;
	}
	else return -1;
}

/**
	@brief pushes an item on the stack
*/

int StackPush(struct Stack * stc, elem_t val) {
	if (StackOk(stc) == STACK_OK) {
		stc->size += 1;
		if (stc->size > stc->capacity - 1) {
			int incr = IncreaseStack(stc);
			if (incr == 0) {
				stc->data[stc->size - 2] = val;
				stc->data[stc->size - 1] = CANARY;
			}
			else return -1;
		}
		else {
			stc->data[stc->size - 2] = val;
			stc->data[stc->size - 1] = CANARY;
		}
		return 0;
	}
	else return -1;
}

/**
	@brief expands stack memory
*/

int IncreaseStack(struct Stack * stc) {
	if (StackOk(stc) == STACK_OK) {
		stc->data = (elem_t*)realloc(stc->data, stc->capacity *= 2);
		if (stc->data == NULL) {
			printf("Memory is over, the array can no longer expand\n");
			return -1;
		}
		stc->capacity *= 2;
		return 0;
	}
	else return -1;
}

/**
	@brief removes a stack item and returns it
*/

elem_t StackPop(struct Stack * stc) {
	if (StackOk(stc) == STACK_OK) {
		elem_t val = stc->data[stc->size - 2];
		stc->data[stc->size - 2] = CANARY;
		stc->data[stc->size - 1] = POISON;
		stc->size -= 1;
		return val;
	}
	else return -1;
}

/**
	@brief checks stack
*/

int StackOk(struct Stack * stc)
{
	if (stc == NULL || stc->canary1 != signal || stc->canary2 != signal || stc->capacity <= 0 || stc->data == NULL) {
		return -1;
	}
	else
		return STACK_OK;
}

/**
	@brief prints stack contents
*/

int StackDump(struct Stack * stc) {
	printf("Stack_t \"stc\" [0x %09x]\n", stc);
	printf("{\ndata[%d] = 0x %09x\n	{\n", stc->capacity, stc->data);
	for (int i = 0; i < stc->capacity; i++) {
		if (stc->data[i] != POISON) {
			(printf("	*[%d] = %lg\n", i, stc->data[i]));
		}
		if (stc->data[i] == POISON) {
			(printf("	[%d] = %lg (POISON!)\n", i, stc->data[i]));
		}
	}
	printf("	}\nsize = %d\n}\n", stc->size);
	return 0;
}
