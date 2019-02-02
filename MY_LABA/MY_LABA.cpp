#include <stdio.h>

void read_laba(double * i_data, double * u_data, int size, FILE * laba_data);
void write_laba(double * i_data, double * u_data, int size, FILE * laba_result);
void write_to_excel(double * i_data, double * u_data, int size, FILE * laba_excel);
double R_average(double * i_data, double * u_data, int size);
const int FILE_NOT_OPEN = -1;

int laba()
{
    FILE * laba_data = fopen("laba_data.txt", "r");
    FILE * laba_result = fopen("laba_result.txt", "w");
    FILE * laba_excel = fopen("laba_excel.csv", "w");
    if (laba_data == NULL || laba_result == NULL && laba_excel == NULL)
    {
        printf("ERROR!!! FILE HAS NOT BEEN OPENED\n");
        return FILE_NOT_OPEN;
    }
    const int size = 10;
    double i_data[size] = {};
    double u_data[size] = {};

    read_laba(i_data, u_data, size, laba_data);

    write_laba(i_data, u_data, size, laba_result);

    write_to_excel(i_data, u_data, size, laba_excel);

    fprintf(laba_result, "______Average Resistance:___R = %.2lf Om___________", R_average(i_data, u_data, size));

    fclose(laba_data);
    fclose(laba_result);
    fclose(laba_excel);
    return 0;
}

void read_laba(double * i_data, double * u_data, int size, FILE * laba_data)
{
    for(int j = 1; j <= size; ++j)
    {
        fscanf(laba_data, "%lf %lf", &u_data[j], &i_data[j]);
    }
}

void write_laba(double * i_data, double * u_data, int size, FILE * laba_result)
{
    for(int j = 1; j <= size; ++j)
    {
        fprintf(laba_result, "%2d) U = %6.2lf mV  || I = %6.2lf mA || R = %4.2lf Om\n", j, u_data[j], i_data[j], u_data[j] / i_data[j]);
    }
}

void write_to_excel(double * i_data, double * u_data, int size, FILE * laba_excel)
{
    for(int j = 1; j <= size; ++j)
    {
        fprintf(laba_excel, "%.2lf;\n", u_data[j] / i_data[j]);
    }
}

double R_average(double * i_data, double * u_data, int size)
{
    double R = 0;
    for(int i = 1; i <= size; ++i)
        R += u_data[i] / i_data[i];
    R = R / size;
    return R;
}

int main()
{
    int result = laba();
    if (result == FILE_NOT_OPEN)
    {
        return FILE_NOT_OPEN;
    }
    printf("#DONE\n     #KONYK M.A.");
    return 0;
}

