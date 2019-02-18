#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "CPU_MK_12.h"
#include "C:\Users\Михаил\source\repos\Processor_projects\CPU_MK_12\CPU_MK_12\CPU_MK_12.h"
#include "C:\Users\Михаил\source\repos\Processor_projects\CPU_MK_12\CPU_MK_12\Stack\Stack.h"
#include "C:\Users\Михаил\source\repos\Processor_projects\ServiceIdentifiers.h"


struct CPU {															//--------------
	double ax;															//
	double bx;															// CPU Registers
	double cx;															//
	double dx;															//--------------
	double * memory;													// Memory Segment
	double * commands;													// Code Segment
	int * labels_segment;												// Labels Segment
	struct Stack * CPU_STACK;											// Stack
																		//--------------
};

int DoProgramm(struct CPU * MY_CPU, double * commands) {
	if (MY_CPU == NULL || commands == NULL) {
		printf("CPU was broken, or your commad list isn't correct!\n");
		return PTR_ERROR;
	}

	int ret = 0;
	int curpos = 0;

	while (ret != CMD_END) {
		ret = ExecuteCommand((int) MY_CPU->commands[curpos], MY_CPU, MY_CPU->commands, &curpos);
		
		if (ret != 0 && ret != CMD_END) {
			return EXECUTION_ERROR;
		}
	}
	return 0;
}

int ExecuteCommand(int com, struct CPU * MY_CPU, double * commands, int * curpos) {
	if (com <= 0 || commands == NULL || curpos == NULL) return EXECUTION_ERROR;

	switch (com) {
	#define DEF_CMD(name, num, CODE_ASM, CODE_CPU)      \
        case (num):                                     \
        {                                               \
            CODE_CPU                                    \
														\
        }

	#include "C:\Users\Михаил\source\repos\Processor_projects\CPU_MK_12\CPU_MK_12\commands.h"
	}
	return 0;
}

double* GetRegValue(struct CPU * MY_CPU, const int reg_code) {
	if (MY_CPU == NULL) return NULL;

	if (reg_code == 'a')
		return &(MY_CPU->ax);
	if (reg_code == 'b')
		return &(MY_CPU->bx);
	if (reg_code == 'c')
		return &(MY_CPU->cx);
	if (reg_code == 'd')
		return &(MY_CPU->dx);

	else printf("Incorret register code!!!\n");
		return NULL;
}



int InitializeCPU(struct CPU * MY_CPU, int code_size) {
	if (MY_CPU == NULL) return PTR_ERROR;

	MY_CPU->memory = (double *)calloc(MEMORY_SIZE, sizeof(double));
	MY_CPU->commands = (double *)calloc(code_size, sizeof(double));
	MY_CPU->labels_segment = (int *)calloc(LABELS_COUNT, sizeof(int));
	MY_CPU->ax = 0;
	MY_CPU->bx = 0;
	MY_CPU->cx = 0;
	MY_CPU->dx = 0;
	MY_CPU->CPU_STACK = init_stack();

	return 0;
}

size_t  FileSize(FILE * bytecod) {
	if (bytecod == NULL) return FILE_ERROR;

	int size = 0;
	int curpos = 0;
	curpos = ftell(bytecod);
	fseek(bytecod, 0, SEEK_END);
	size = ftell(bytecod);
	fseek(bytecod, 0, curpos);

	return size;
}

int MemoryBytecode(FILE * bytecode_file, double * commands) {
	if (bytecode_file == NULL || commands == NULL) {
		return FILE_ERROR;
	}

	double curr_command = POISON;
	int current_index = 0;
	
	while (fscanf(bytecode_file, "%lf", &curr_command) != EOF) {
		commands[current_index] = curr_command;
		current_index += 1;
	}
	fseek(bytecode_file, 0, SEEK_SET);
	return 0;
}

int ReadLabels(double * commands, int * labels, size_t code_size) {
	for (unsigned i = 0; i < (int) code_size; ++i) {
		if (commands[i] == CMD_LABEL) {
			int label_number = (int) commands[i + 1];
			if (label_number > 0 && label_number < LABELS_COUNT)
				labels[label_number] = i + 2;
			else
				return LABEL_ERROR;
		}
	}
	return 0;
}


int main() {
	FILE * bytecode_file = fopen("C:/Users/Михаил/source/repos/Processor_projects/Source_code/bytecod.txt", "r");
	if (bytecode_file == NULL) {
		printf("File wasn't opened!\n");
		return FILE_ERROR;
	}

	int ret = 0;
	struct CPU MY_CPU;
	size_t code_size = FileSize(bytecode_file);

	ret = InitializeCPU(&MY_CPU, code_size);
	if (ret != 0) return ret;

	ret = MemoryBytecode(bytecode_file, MY_CPU.commands);
	if (ret != 0) return ret;

	fclose(bytecode_file);

	ret = ReadLabels(MY_CPU.commands, MY_CPU.labels_segment, code_size);
	if (ret != 0) return ret;

	return DoProgramm(&MY_CPU, MY_CPU.commands);
}