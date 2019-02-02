#include <stdio.h>
#include <math.h>
#include <conio.h>

/**
@mainpage A program for solving a quadratic equation.
*/

/// Solves a quadratic equation;
int solve_square(float a, float b, float c, float * x1, float * x2);

/// Solves the quadratic equation and displays the result of the solution;
int solve_and_print(float a, float b, float c, float x1, float x2);

/// Solves the linear equation
int solve_line(float b, float c, float * x1);

/// Variable setting accuracy. Used to compare rational numbers;
const float Tol = 0.0001;

/// Return function enumeration
enum Roots_Amount
{
    INF = 1000,
    NROOTS_0 = 0,
    NROOTS_1 = 1,
    NROOTS_2 = 2,
    ERROR = 13
};

/**
@brief The main function,\n
asks the user to enter the coefficients,\n
checks their correctness\n
and calls the function to solve the equation.
@return 1) 0 if program the program was successful;
@return 2) ERROR if if an error occurred.
*/

int main()
{
    printf("_____Quadratic equation._______\n");
    printf("Enter the coefficients a, b, c:\n");
	float a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    scanf("%f %f %f", &a, &b, &c);
    if (!isfinite(a) || !isfinite(b) || !isfinite(c))
    {
        printf("Error: Incorrect coefficients entered, try again. \n");
        getch();
        return ERROR;
    }
    solve_and_print(a, b, c, x1, x2);
    printf("\n#by Konyk Mikhail, 02.10.18");
    getch();
    return 0;
}

/**
@function
@brief Display Values: Displays "Infinite Number of Roots"
in the case of an infinite number of roots; \n
Displays "Equation has no roots" in case there are no roots; \n
Displays a single root if the equation is linear; \n
Deduces the two roots of a quadratic equation if D> 0;
@param a, b, c are the coefficients of a quadrant equation.
@param x1, x2 - roots of a quadratic equation
@return 1) ERROR if coefficients are incorrect;
@return 2) Nothing if it is all right.
*/

int solve_and_print(float a, float b, float c, float x1, float x2)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c))
    {
        printf("Error: Incorrect coefficients entered, try again. \n");
        return ERROR;
    }
    enum Roots_Amount n_roots = solve_square(a, b, c, &x1, &x2);
    switch(n_roots)
    {
        case NROOTS_0:  printf("The equation has no roots.\n");
                 break;
        case NROOTS_1:  printf("The equation is linear.\nx = %.2f\n", x1);
                 break;
        case NROOTS_2:  printf("x1 = %.2f; \nx2 = %.2f; \n", x1, x2);
                 break;
        case INF: printf("Infinite number of roots.\n");
                 break;
        case ERROR:  printf("An error has occurred, try again.");
                 break;
    }
}

/**
@function
@param a, b, c are the coefficients of a quadrant equation.
@param x1, x2 are pointers to the roots of a quadratic equation.
@return 1) ERROR (= 13) - Error, incorrect coefficients entered;
@return 2) NROOTS_0 (= 0) - The equation has no roots, D <0;
@return 3) Returns 1 if the equation is linear (a = 0) and has one root;
@return 4) Returns 2 if the equation has 2 roots;
@return 5) INF (= 1000) - Infinite number of roots;
*/

int solve_square(float a, float b, float c, float * x1, float * x2)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c))
    {
        printf("Error: Incorrect coefficients entered, try again. \n");
        return ERROR;
    }
    if (fabs(a) < Tol)
        return solve_line(b, c, x1);
    else
    {
        float discr = b * b - 4 * a * c;
        if (discr >= 0)
        {
            float sq_discr = sqrt(discr);
            *x1 = (-b + sq_discr) / (2 * a);
            *x2 = (-b - sq_discr) / (2 * a);
            return NROOTS_2;
        }
        else return NROOTS_0;
    }
}

/**
@function
@brief If the equation is linear (a = 0), this function is called.
@param a, b - coefficients of the equation;
@param x1 is a pointer to the root of the equation.
@return 1) ERROR (= 13) - Error, incorrect coefficients entered;
@return 2) INF (= 1000) - Infinite number of roots;
@return 3) NROOTS_0 (= 0) - The equation has no roots;
@return 4) NROOTS_1 (= 1) - The equation has one root.
*/

int solve_line(float b, float c, float * x1)
{
    if (!isfinite(b) || !isfinite(c))
    {
        printf("Error: Incorrect coefficients entered, try again. \n");
        return ERROR;
    }
    if (fabs(b) < Tol && fabs(c) < Tol)
    {
        return INF;
    }
    else if (fabs(b) < Tol)
    {
        return NROOTS_0;
    }
    else
    {
        *x1 = -b / c;
        return NROOTS_1;
    }
}
