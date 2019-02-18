
/*
*/
int DoProgramm(struct CPU * MY_CPU, double * commands);


/*
*/
int InitializeCPU(struct CPU * MY_CPU, int code_size);


/*
*/
size_t FileSize(FILE * bytecode_file);

/*
*/
int MemoryBytecode(FILE * bytecode_file, double * commands);

/*
*/
int ReadLabels(double * commands, int * labels, size_t code_size);

/*
*/
int ExecuteCommand(int com, struct CPU * MY_CPU,
	double * commands, int * curpos);

/*
*/
double* GetRegValue(struct CPU * MY_CPU, const int reg_code);