//
//      double-matrix-multip.c
//      Alternative matrix multiplication by using the least efficient way it is possible :)
//      Oguz Alp Cakmak - Galatasaray University
//      April 2nd, 2022
//
//      Sorry for variable names, it's too hard to find cool names :(
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct double_mcols
{
    double mval;
} mcols;

typedef struct double_matrix //I had to use this method to return matrices.
{
    mcols *mcol;
} dmatrix;

double randfrom(double min, double max) //Simple random double value generation method.
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

dmatrix *make_matrix(int rows, int columns) //Creates 2D matrix array.
{
    dmatrix *new_matrix = (dmatrix *)(malloc(sizeof(dmatrix)*rows));
    for(int i = 0; i < rows; i++)
    {
        new_matrix[i].mcol = (mcols *)(malloc(sizeof(mcols)*columns));
    }
    return new_matrix;
}

dmatrix *matrix_multiplier(dmatrix *first, int f_rows, int f_columns, dmatrix *second, int s_rows, int s_columns)
{
    dmatrix *end_product = make_matrix(f_rows, s_columns);

    for(int i = 0; i < f_rows; i++)
    {
        for(int j = 0; j < s_columns; j++)
        {
            end_product[i].mcol[j].mval = 0;
            for(int k = 0; k < f_columns; k++)
            {
                end_product[i].mcol[j].mval += first[i].mcol[k].mval * second[k].mcol[j].mval;
            }
        }
    }

    return end_product;

}

void print_matrices(dmatrix *first, int f_rows, int f_columns, dmatrix *second, int s_rows, int s_columns, dmatrix *product)
{
    printf("\n"); //Not the prettiest way to print I know.

    for(int i = 0; i < s_rows; i++)
    {
        for(int j = 0; j < f_columns; j++) printf("\t");

        for(int j = 0; j < s_columns; j++)
        {
            printf("\t%5.2f", second[i].mcol[j].mval);
        }
        printf("\n\n");
    }

    for(int i = 0; i < f_rows; i++)
    {
        for(int j = 0; j < f_columns; j++)
        {
            printf("\t%5.2f", first[i].mcol[j].mval);
        }

        for(int j = 0; j < s_columns; j++)
        {
            printf("\t%5.2f", product[i].mcol[j].mval);
        }
        printf("\n\n");
    }
}

void fill_matrix(dmatrix *matrix, int rows, int columns, double min, double max)
{
    
    for(int i = 0; i < rows; i++) //Fills matrix with random values.
    {
        for(int j = 0; j < columns; j++)
        {
            matrix[i].mcol[j].mval = randfrom(min, max);
        }
    }
    
}

int main(void)
{
    
    time_t *tp = NULL;
    srand(time(tp));

    int fm_row, fm_col, sm_row, sm_col;

    do
    {
        printf("Enter line length of first matrix -> ");
        scanf("%d", &fm_row);
        printf("Enter column length of first matrix -> ");
        scanf("%d", &fm_col);
        printf("Enter line length of second matrix -> ");
        scanf("%d", &sm_row);
        printf("Enter column length of second matrix -> ");
        scanf("%d", &sm_col);
    } while (fm_col != sm_row); //Hope whoever uses it figures this out.

    dmatrix *first_matrix = make_matrix(fm_row, fm_col);
    fill_matrix(first_matrix, fm_row, fm_col, -1, 1);

    dmatrix *second_matrix = make_matrix(sm_row, sm_col);
    fill_matrix(second_matrix, sm_row, sm_col, -1, 1);

    dmatrix *product = matrix_multiplier(first_matrix, fm_row, fm_col, second_matrix, sm_row, sm_col);
    
    print_matrices(first_matrix, fm_row, fm_col, second_matrix, sm_row, sm_col, product);

    return 0;
}