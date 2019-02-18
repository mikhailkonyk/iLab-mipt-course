#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "C:\Users\Михаил\source\repos\Processor_projects\ServiceIdentifiers.h"

int AssembleCode(FILE * commands, FILE * bytecode_file);
int CheckCommand(char * line, FILE * bytecode_file, FILE * commands);

int AssembleCode(FILE * commands, FILE * bytecode_file) {
	if (bytecode_file == NULL || commands == NULL) return FILE_ERROR;

	char * line = (char *)calloc(INITIAL_LINE, sizeof(char));
	int curpos = 0;

	while (fscanf(commands, " %128s", line) != EOF) {
		int ret = CheckCommand(line, bytecode_file, commands);
		if (ret < 0) return ret;
	}
	return 0;
}

int CheckCommand(char * line, FILE * bytecode_file, FILE * commands) {
	if (line == NULL) return PTR_ERROR;
	if (bytecode_file == NULL || commands == NULL) return FILE_ERROR;
	
	char * help_line = (char *)calloc(INITIAL_LINE, sizeof(char));

	int arg = 0;
	char ch_arg1 = 0;
	char ch_arg2 = 0;
	char reg_name = 0;

	#define DEF_CMD(name, num, CODE_ASM, CODE_CPU) \
    if (strcmp(name, line) == 0){                  \
                                                   \
        CODE_ASM                                   \
												   \
    }

	#include "C:\Users\Михаил\source\repos\Processor_projects\CPU_MK_12\CPU_MK_12\commands.h"

	return 0;
}

int main()
{
	FILE * commands = fopen("C:/Users/Михаил/source/repos/Processor_projects/Source_code/commands.txt", "rb");
	FILE * bytecode_file = fopen("C:/Users/Михаил/source/repos/Processor_projects/Source_code/bytecod.txt", "w");

	if (commands == NULL || bytecode_file == NULL) {
		return FILE_ERROR;
	}

	int ret = AssembleCode(commands, bytecode_file);
	if (ret == 0) {
		printf("Assembly was successful.\n");
		fclose(commands);
		fclose(bytecode_file);
	}
	
	return ret;
}