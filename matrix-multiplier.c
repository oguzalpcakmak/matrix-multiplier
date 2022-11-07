//
//      matrix-multiplier.c
//      Alternative matrix multiplication by using the least efficient way it is possible :)
//      Oguz Alp Cakmak - Galatasaray University
//      April 2nd, 2022
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct columns
{
    double val;
} cols;

typedef struct matrix // I had to use this method to return matrices.
{
    cols *col;
} matrix;

double randfrom(double min, double max) // Simple random double value generation method.
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

matrix *new_matrix(int r, int c) // Creates 2D matrix array.
{
    matrix *tmp_matrix = (matrix *)(malloc(sizeof(matrix) * r));
    for (int i = 0; i < r; i++)
    {
        tmp_matrix[i].col = (cols *)(malloc(sizeof(cols) * c));
    }
    return tmp_matrix;
}

matrix *matrix_multiplier(matrix *f, int f_r, int f_c, matrix *s, int s_r, int s_c)
{
    if (f_c != s_r)
    {
        printf("Insert error handler here. :)");
    }

    matrix *t = new_matrix(f_r, s_c);

    for (int i = 0; i < f_r; i++)
    {
        for (int j = 0; j < s_c; j++)
        {
            t[i].col[j].val = 0;
            for (int k = 0; k < f_c; k++)
            {
                t[i].col[j].val += f[i].col[k].val * s[k].col[j].val;
            }
        }
    }

    return t;
}

void print_matrices(matrix *f, int f_r, int f_c, matrix *s, int s_r, int s_c, matrix *t)
{
    // Not the prettiest way to print I know.
    printf("\n");

    for (int i = 0; i < s_r; i++)
    {
        for (int j = 0; j < f_c; j++)
            printf("\t");

        for (int j = 0; j < s_c; j++)
        {
            printf("\t%5.2f", s[i].col[j].val);
        }
        printf("\n\n");
    }

    for (int i = 0; i < f_r; i++)
    {
        for (int j = 0; j < f_c; j++)
        {
            printf("\t%5.2f", f[i].col[j].val);
        }

        for (int j = 0; j < s_c; j++)
        {
            printf("\t%5.2f", t[i].col[j].val);
        }
        printf("\n\n");
    }
}

void fill_matrix(matrix *m, int r, int c, double min, double max)
{
    // Fills matrix with random values.
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            m[i].col[j].val = randfrom(min, max);
        }
    }
}

int main(void)
{

    time_t *t = NULL;
    srand(time(t));

    int f_r, f_c, s_r, s_c;

    do
    {
        printf("Enter rows of first matrix -> ");
        scanf("%d", &f_r);
        printf("Enter columns of first matrix -> ");
        scanf("%d", &f_c);
        printf("Enter rows of second matrix -> ");
        scanf("%d", &s_r);
        printf("Enter columnns of second matrix -> ");
        scanf("%d", &s_c);
    } while (f_c != s_r); // Safety first!

    matrix *first_matrix = new_matrix(f_r, f_c);
    fill_matrix(first_matrix, f_r, f_c, -1, 1);

    matrix *second_matrix = new_matrix(s_r, s_c);
    fill_matrix(second_matrix, s_r, s_c, -1, 1);

    matrix *third_matrix = matrix_multiplier(first_matrix, f_r, f_c, second_matrix, s_r, s_c);

    print_matrices(first_matrix, f_r, f_c, second_matrix, s_r, s_c, third_matrix);

    return 0;
}
