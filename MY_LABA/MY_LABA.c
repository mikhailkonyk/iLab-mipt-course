#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int read_laba(double * i_data, double * u_data, FILE * laba_data);
int write_laba(double * i_data, double * u_data, double * r_data, FILE * laba_result);
int write_to_excel(double * r_data, FILE * laba_excel);
int R_average(double * r_data, double * R);
int exp_error(double * i_data, double * u_data, double * r_data, double * R_err);

const int size = 10;
const double TOL = 0.00001;

const double V_MAX = 300;
const double I_MAX = 99;
const double V_err = 1.5;
const double I_err = 0.75;

enum ERRORS
{
    FILE_NOT_OPEN = -1,
    INCORRECT_VALUE = -2,
    POINTER_ERROR = -3,
    LABA_WAS_NOT_SUCCESS = -1000
};

int laba()
{
    FILE * laba_data = fopen("laba_data.txt", "r");
    FILE * laba_result = fopen("laba_result.txt", "w");
    FILE * laba_excel = fopen("laba_excel.csv", "w");
    if (laba_data == NULL || laba_result == NULL && laba_excel == NULL)
    {
        printf("ERROR!!! FILE HAS NOT BEEN OPENED\n");
        return LABA_WAS_NOT_SUCCESS;
    }
    double * i_data = (double *) calloc(size, sizeof(double));
    double * u_data = (double *) calloc(size, sizeof(double));
    double * r_data = (double *) calloc(size, sizeof(double));
    double R = 0; /// R_Average
    double R_err = 0;
    int ECHO = 0;
    ECHO = read_laba(i_data, u_data, laba_data);
    if (ECHO == POINTER_ERROR)
        return LABA_WAS_NOT_SUCCESS;

    ECHO = write_laba(i_data, u_data, r_data, laba_result);
    if (ECHO == POINTER_ERROR || ECHO == INCORRECT_VALUE || ECHO == FILE_NOT_OPEN)
        return LABA_WAS_NOT_SUCCESS;

    ECHO = write_to_excel(r_data, laba_excel);
    if (ECHO == POINTER_ERROR || ECHO == FILE_NOT_OPEN)
        return LABA_WAS_NOT_SUCCESS;

    ECHO = R_average(r_data, &R);
    if (ECHO == POINTER_ERROR)
        return LABA_WAS_NOT_SUCCESS;

    ECHO = exp_error(i_data, u_data, r_data, &R_err);
    if (ECHO == POINTER_ERROR)
        return LABA_WAS_NOT_SUCCESS;
    fprintf(laba_result, "Average Resistance:  R = %.2f +- %.2f Om (E = %.2f )", R, R_err, (R_err / R));

    free(i_data);
    free(u_data);
    free(r_data);
    fclose(laba_data);
    fclose(laba_result);
    fclose(laba_excel);

    return 0;
}

int read_laba(double * i_data, double * u_data, FILE * laba_data)
{
    if (i_data == NULL || u_data == NULL)
    {
        printf("ERROR!!! Null pointer");
        return POINTER_ERROR;
    }
    for(int j = 1; j <= size; ++j)
    {
        fscanf(laba_data, "%lf %lf", &u_data[j], &i_data[j]);
    }
    return 0;
}

int write_laba(double * i_data, double * u_data, double * r_data, FILE * laba_result)
{
    if (i_data == NULL || u_data == NULL || r_data == NULL)
    {
        printf("ERROR!!! Null pointer");
        return POINTER_ERROR;
    }
    else if (laba_result == NULL)
    {
        printf("ERROR!!! Result file wasn't found");
        return FILE_NOT_OPEN;
    }

    for(int j = 1; j <= size; ++j)
    {
        if (fabs(i_data[j]) < TOL)
            return INCORRECT_VALUE;

        r_data[j] = u_data[j] / i_data[j];
        fprintf(laba_result, "%2d) U = %6.2f mV  || I = %6.2f mA || R = %4.2f Om\n", j, u_data[j], i_data[j], r_data[j]);
    }
    return 0;
}

int write_to_excel(double * r_data, FILE * laba_excel)
{
    if (r_data == NULL)
    {
        printf("ERROR!!! Null pointer");
        return POINTER_ERROR;
    }
    else if (laba_excel == NULL)
    {
        printf("ERROR!!! Result file wasn't found");
        return FILE_NOT_OPEN;
    }

    for(int j = 1; j <= size; ++j)
    {

        fprintf(laba_excel, "%.2f;\n", r_data[j]);
    }

    return 0;
}

int R_average(double * r_data, double * R)
{
    if (r_data == NULL)
    {
        printf("ERROR!!! Null pointer");
        return POINTER_ERROR;
    }

    for(int i = 1; i <= size; ++i)
    {
        *R += r_data[i];
    }

    *R = *R / size;

    return 0;
}

int exp_error(double * i_data, double * u_data, double * r_data, double * R_err)
{
    if (r_data == NULL)
    {
        printf("ERROR!!! Null pointer");
        return POINTER_ERROR;
    }

    double V_square_average = 0;
    double I_square_average = 0;
    double VI_average = 0;
    for (int i = 0; i < size; ++i)
    {
        V_square_average += u_data[i] * u_data[i];
        I_square_average += i_data[i] * i_data[i];
        VI_average += i_data[i] * u_data[i];
    }
    V_square_average /= size;
    I_square_average /= size;
    VI_average /= size;
    double R_1 = VI_average / I_square_average;

    double rand_err = (1 / sqrt((double) size)) * sqrt( (V_square_average) / (I_square_average) - R_1 * R_1);

    double syst_err = R_1 * sqrt( (V_err / V_MAX) * (V_err / V_MAX) + (I_err / I_MAX) * (I_err / I_MAX) );

    *R_err = sqrt( (rand_err) * (rand_err) + (syst_err) * (syst_err));

    return 0;
}

int main()
{
    int result = laba();
    if (result == LABA_WAS_NOT_SUCCESS)
    {
        return LABA_WAS_NOT_SUCCESS;
    }
    printf("#DONE\n     #KONYK M.A. 01.11.18");
    return 0;
}

