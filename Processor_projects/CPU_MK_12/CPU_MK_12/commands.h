
#define REG_INSTRUCTION  symbol_ptr != NULL &&															  \
						 (reg_name == 'a' || reg_name == 'b' || reg_name == 'c' || reg_name == 'd') &&	  \
						 symbol_ptr[-2] == ' '
						 
				

#define RAM_INSTRUCTION symbol_ptr != NULL 	&&															  \
						sscanf(symbol_ptr, "%c%d%c",&ch_arg1, &arg, &ch_arg2) == 3 &&					  \
						ch_arg1 == '[' && ch_arg2 == ']' 
						


#define RAM_REG_INSTRUCTION symbol_ptr != NULL &&														  \
							sscanf(symbol_ptr, "%c%cx%c", &ch_arg1, &reg_name, &ch_arg2) == 3 &&		  \
							ch_arg1 == '[' && ch_arg2 == ']' &&											  \
							(reg_name == 'a' || reg_name == 'b' || reg_name == 'c' || reg_name == 'd')


#define RAM_REG_SUM_INSTRUCTION symbol_ptr != NULL && \
								sscanf(symbol_ptr, "[ %cx + %d ]", &reg_name, &arg) == 2 &&				  \
								(reg_name == 'a' || reg_name == 'b' || reg_name == 'c' || reg_name == 'd')\
	


//__________________________________________________________
//															|
// POP BLOCK												|
//__________________________________________________________|

DEF_CMD("pop", CMD_POP_RAM_REG_SUM, 
	{
	//fscanf(commands, "%128[^\n]", help_line);
	fgets(help_line, 128, commands);
	const char * symbol_ptr = strchr(help_line, '[');

	if (RAM_REG_SUM_INSTRUCTION) {
		fprintf(bytecode_file, "%d %d %d ", CMD_POP_RAM_REG_SUM, reg_name, arg);
		return 0;
		}
}, {
	int reg_code = (int) MY_CPU->commands[*curpos + 1];
	int cell_1 = (int) *GetRegValue(MY_CPU, reg_code);
	int cell_2 = (int) MY_CPU->commands[*curpos + 2];
	int dest = cell_1 + cell_2;
	double value = StackPop(MY_CPU->CPU_STACK);
	if (dest < MEMORY_SIZE && dest >= 0) {
		MY_CPU->memory[dest] = value;
		*curpos += 3;
		break;
	}
	else return MEMORY_ERROR;
})

DEF_CMD("pop", CMD_POP_RAM, {
	const char * symbol_ptr = strchr(help_line, '[');
	
	if (RAM_INSTRUCTION) {
		fprintf(bytecode_file, "%d %d ", CMD_POP_RAM, arg);
		return 0;
	}
}, {
	int dest = (int) MY_CPU->commands[*curpos + 1];
	double value = StackPop(MY_CPU->CPU_STACK);
	if (dest < MEMORY_SIZE && dest >= 0) {
		MY_CPU->memory[dest] = value;
		*curpos += 2;
		break;
	}
	else return MEMORY_ERROR;
})

DEF_CMD("pop", CMD_POP_RAM_REG, 
	{
	const char * symbol_ptr = strchr(help_line, '[');

	if (RAM_REG_INSTRUCTION) {
		fprintf(bytecode_file, "%d %d ", CMD_POP_RAM_REG, reg_name);
		return 0;
	}
}, {
	int reg_code = (int) MY_CPU->commands[*curpos + 1];
	int cell_1 = (int) *GetRegValue(MY_CPU, reg_code);
	int dest = cell_1;
	double value = StackPop(MY_CPU->CPU_STACK);
	if (dest < MEMORY_SIZE && dest >= 0) {
		MY_CPU->memory[dest] = value;
		*curpos += 2;
		break;
	}
	else return MEMORY_ERROR;
})

DEF_CMD("pop", CMD_POP_REG, 
	{
	const char * symbol_ptr = strchr(help_line, 'x');

	if (symbol_ptr != NULL)
		reg_name = symbol_ptr[-1];
	
	if (REG_INSTRUCTION) {
		
		fprintf(bytecode_file, "%d %d ", CMD_POP_REG, reg_name);
		return 0;
	}
}, {
	int reg_code = (int) MY_CPU->commands[*curpos + 1];
	*GetRegValue(MY_CPU, reg_code) = StackPop(MY_CPU->CPU_STACK);
	*curpos += 2;
	break;
	})


DEF_CMD("pop", CMD_POP, 
	{
	if (help_line[0] == 13) {
		fprintf(bytecode_file, "%d ", CMD_POP);
		return 0;
	}
}, {
		StackPop(MY_CPU->CPU_STACK);
		*curpos += 1;
		break;
})

//__________________________________________________________
//															|
// PUSH BLOCK												|
//__________________________________________________________|


DEF_CMD("push", CMD_PUSH_RAM_REG_SUM, 
	{
	//fscanf(commands, "%128[^\n]", help_line);
	fgets(help_line, INITIAL_LINE, commands);
	char * symbol_ptr = strchr(help_line, '[');

	if (RAM_REG_SUM_INSTRUCTION) {
		fprintf(bytecode_file, "%d %d %d ", CMD_PUSH_RAM_REG_SUM, reg_name, arg);
		return 0;
	}
}, {
	int reg_code = (int) MY_CPU->commands[*curpos + 1];
	int cell_1 = (int) *GetRegValue(MY_CPU, reg_code);
	int cell_2 = (int) MY_CPU->commands[*curpos + 2];
	int dest = cell_1 + cell_2;
	if (dest < MEMORY_SIZE && dest >= 0) {
		double value = MY_CPU->memory[dest];
		StackPush(MY_CPU->CPU_STACK, value);
		*curpos += 3;
		break;
	}
	
	else return MEMORY_ERROR;

})

DEF_CMD("push", CMD_PUSH_RAM_REG, 
	{
	const char * symbol_ptr = strchr(help_line, '[');
	if (RAM_REG_INSTRUCTION) {
		fprintf(bytecode_file, "%d %d ", CMD_PUSH_RAM_REG, reg_name);
		return 0;
	}
}, {
	int reg_code = (int)MY_CPU->commands[*curpos + 1];
	int dest = (int)*GetRegValue(MY_CPU, reg_code);
	if (dest < MEMORY_SIZE && dest >= 0) {
		double value = MY_CPU->memory[dest];
		StackPush(MY_CPU->CPU_STACK, value);
		*curpos += 2;
		break;
	}

	else return MEMORY_ERROR;
})

DEF_CMD("push", CMD_PUSH_RAM, 
	{
	const char * symbol_ptr = strchr(help_line, '[');

	if (RAM_INSTRUCTION) {
		fprintf(bytecode_file, "%d %d ", CMD_PUSH_RAM, arg);
		return 0;
	}
}, {
	int dest = (int)MY_CPU->commands[*curpos + 1];
	if (dest < MEMORY_SIZE && dest >= 0) {
		double value = MY_CPU->memory[dest];
		StackPush(MY_CPU->CPU_STACK, value);
		*curpos += 2;
		break;
	}

	else return MEMORY_ERROR;
})

DEF_CMD("push", CMD_PUSH_REG, 
	{
	const char * symbol_ptr = strchr(help_line, 'x');
	if (symbol_ptr != NULL)
		reg_name = symbol_ptr[-1];

	if (REG_INSTRUCTION) {
		fprintf(bytecode_file, "%d %d ", CMD_PUSH_REG, reg_name);
		return 0;
	}

}, {
	int reg_code = (int)MY_CPU->commands[*curpos + 1];
	double value = *GetRegValue(MY_CPU, reg_code);
	StackPush(MY_CPU->CPU_STACK, value);
	*curpos += 2;
	break;
})

DEF_CMD("push", CMD_PUSH, 
	{
	double number = 0;
	if (sscanf(help_line, "%lf", &number) == 1) {
		fprintf(bytecode_file, "%d %f ", CMD_PUSH, number);
	}
	return 0;

}, {
	double arg = commands[*curpos + 1];
	StackPush(MY_CPU->CPU_STACK, arg);
	*curpos += 2;
	break;
})



//__________________________________________________________
//															|  
// MATH BLOCK											    |
//__________________________________________________________|


DEF_CMD("mul", CMD_MUL, 
	{
	fprintf(bytecode_file, "%d ", CMD_MUL);
	return 0;
}, {
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	double mul = arg1 * arg2;
	StackPush(MY_CPU->CPU_STACK, mul);
	*curpos += 1;
	break;
})

DEF_CMD("div", CMD_DIV, 
	{
	fprintf(bytecode_file, "%d ", CMD_DIV);
	return 0;
}, {
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	if (fabs(arg1) < TOLERANCE) {
		printf("Zero division error!\n");
		return DIVISION_ERROR;
	}
	double div = arg2 / arg1;
	StackPush(MY_CPU->CPU_STACK, div);
	*curpos += 1;
	break;
})

DEF_CMD("sqrt", CMD_SQRT, 
	{
	fprintf(bytecode_file, "%d ", CMD_SQRT);
	return 0;
	}, {
	double arg = StackPop(MY_CPU->CPU_STACK);
	arg = sqrt(arg);
	StackPush(MY_CPU->CPU_STACK, arg);
	*curpos += 1;
	break;
})


DEF_CMD("sum", CMD_SUM, 
	{
	fprintf(bytecode_file, "%d ", CMD_SUM);
	return 0;
}, {
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	double sum = arg1 + arg2;
	StackPush(MY_CPU->CPU_STACK, sum);
	*curpos += 1;
	break;
})

DEF_CMD("sub", CMD_SUB,
	{
	fprintf(bytecode_file, "%d ", CMD_SUB);
	return 0;
}, {
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	double sub = arg2 - arg1;
	StackPush(MY_CPU->CPU_STACK, sub);
	*curpos += 1;
	break;
})

//__________________________________________________________
//															|
// LABEL BLOCK											    |
//__________________________________________________________|

DEF_CMD(":", CMD_LABEL, 
	{
	fscanf(commands, "%d", &arg);
	fprintf(bytecode_file, "%d %d ", CMD_LABEL, arg);
	return 0;
}, {
	*curpos += 2;
	break;
})

DEF_CMD("jmp", CMD_JMP, 
	{
	fscanf(commands, "%d", &arg);
	fprintf(bytecode_file, "%d %d ", CMD_JMP, arg);
	return 0;
}, {
	int label = (int) MY_CPU->commands[*curpos + 1];
	int index = MY_CPU->labels_segment[label];
	*curpos = index;
	break;
})

DEF_CMD("je", CMD_JE, 
	{
	fscanf(commands, "%d", &arg);
	fprintf(bytecode_file, "%d %d ", CMD_JE, arg);
	return 0;
}, {
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	if (fabs(arg1 - arg2) < TOLERANCE) {
		int label = (int) MY_CPU->commands[*curpos + 1];
		int index =  MY_CPU->labels_segment[label];
		*curpos = index;
	}
	else
		*curpos += 2;
	break;
})

DEF_CMD("jne", CMD_JNE, 
	{
	fscanf(commands, "%d", &arg);
	fprintf(bytecode_file, "%d %d ", CMD_JNE, arg);
	return 0;
}, {
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	if (fabs(arg1 - arg2) > TOLERANCE) {
		int label = (int) MY_CPU->commands[*curpos + 1];
		int index = MY_CPU->labels_segment[label];
		*curpos = index;
	}
	else
		*curpos += 2;
	break;
})

DEF_CMD("ja", CMD_JA, 
	{
	fscanf(commands, "%d", &arg);
	fprintf(bytecode_file, "%d %d ", CMD_JA, arg);
	return 0;
}, {
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	if (arg1 > arg2) {
		int label = (int) MY_CPU->commands[*curpos + 1];
		int index = MY_CPU->labels_segment[label];
		*curpos = index;
	}
	else
		*curpos += 2;
	break;
})

DEF_CMD("jae", CMD_JAE, 
	{
	fscanf(commands, "%d", &arg);
	fprintf(bytecode_file, "%d %d ", CMD_JAE, arg);
	return 0;
}, {
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	if (arg1 > arg2 || fabs(arg1 - arg2) < TOLERANCE) {
		int label = (int) MY_CPU->commands[*curpos + 1];
		int index = MY_CPU->labels_segment[label];
		*curpos = index;
	}
	else
		*curpos += 2;
	break;
})

DEF_CMD("jb", CMD_JB, 
	{
	fscanf(commands, "%d", &arg);
	fprintf(bytecode_file, "%d %d ", CMD_JB, arg);
	return 0;
}, { 
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	if (arg1 < arg2) {
		int label = (int) MY_CPU->commands[*curpos + 1];
		int index = MY_CPU->labels_segment[label];
		*curpos = index;
	}
	else
		*curpos += 2;
	break;
})

DEF_CMD("jbe", CMD_JBE, 
	{
	fscanf(commands, "%d", &arg);
	fprintf(bytecode_file, "%d %d ", CMD_JBE, arg);
	return 0;
}, {
	double arg2 = StackPop(MY_CPU->CPU_STACK);
	double arg1 = StackPop(MY_CPU->CPU_STACK);
	if (arg1 < arg2 || fabs(arg1 - arg2) < TOLERANCE) {
		int label = (int) MY_CPU->commands[*curpos + 1];
		int index = MY_CPU->labels_segment[label];
		*curpos = index;
	}
	else
		*curpos += 2;
	break;
})

//__________________________________________________________
//															|
// SYSTEM BLOCK											    |
//__________________________________________________________|

DEF_CMD("in", CMD_IN, 
	{
	fprintf(bytecode_file, "%d ", CMD_IN);
	return 0;
}, {
		double coef = 0;
		scanf("%lf", &coef);
		StackPush(MY_CPU->CPU_STACK, coef);
		*curpos += 1;
		break;
})

DEF_CMD("out", CMD_OUT, 
	{
	fprintf(bytecode_file, "%d ", CMD_OUT);
	return 0;
}, {
	double value = StackPop(MY_CPU->CPU_STACK);
	printf("%.3lf\n", value);
	*curpos += 1;
	break;
})

DEF_CMD("start", CMD_START, 
	{
	fprintf(bytecode_file, "%d ", CMD_START);
	return 0;
}, {
	printf("Your program has been launched.\n");
	*curpos += 1;
	break;
})

DEF_CMD("end", CMD_END, 
	{
	fprintf(bytecode_file, "%d ", CMD_END);
	return 0;
}, {
	return CMD_END;
})

DEF_CMD("nan", CMD_NAN, 
	{
	fprintf(bytecode_file, "%d ", CMD_NAN);
	return 0;
}, {
	*curpos += 1;
	break;
})

