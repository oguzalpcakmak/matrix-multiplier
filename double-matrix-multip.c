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

typedef struct double_matrice //I had to use this method to return matrices.
{
    double mval;
    struct double_matrice *mcol;
} dmatrice;

double randfrom(double min, double max) //Simple random double value generation method.
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

dmatrice *make_matrice(int lines, int columns) //Creates 2D matrice array.
{
    dmatrice *new_matrice = (dmatrice *)(malloc(sizeof(dmatrice)*lines));
    for(int i = 0; i < lines; i++)
    {
        new_matrice[i].mcol = (dmatrice *)(malloc(sizeof(dmatrice)*columns));
    }
    return new_matrice;
}

dmatrice *matrice_multiplier(dmatrice *first, int f_lines, int f_columns, dmatrice *second, int s_lines, int s_columns)
{
    dmatrice *end_product = make_matrice(f_lines, s_columns);

    for(int i = 0; i < f_lines; i++)
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

void print_matrices(dmatrice *first, int f_lines, int f_columns, dmatrice *second, int s_lines, int s_columns, dmatrice *product)
{
    printf("\n"); //Not the prettiest way to print I know.

    for(int i = 0; i < s_lines; i++)
    {
        for(int j = 0; j < f_columns; j++) printf("\t");

        for(int j = 0; j < s_columns; j++)
        {
            printf("\t%5.2f", second[i].mcol[j].mval);
        }
        printf("\n\n");
    }

    for(int i = 0; i < f_lines; i++)
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

void fill_matrice(dmatrice *matrice, int lines, int columns, double min, double max)
{
    
    for(int i = 0; i < lines; i++) //Fills matrice with random values.
    {
        for(int j = 0; j < columns; j++)
        {
            matrice[i].mcol[j].mval = randfrom(min, max);
        }
    }
    
}

int main(void)
{
    
    time_t *tp = NULL;
    srand(time(tp));

    int fm_lin, fm_col, sm_lin, sm_col;

    do
    {
        printf("Enter line length of first matrice -> ");
        scanf("%d", &fm_lin);
        printf("Enter column length of first matrice -> ");
        scanf("%d", &fm_col);
        printf("Enter line length of second matrice -> ");
        scanf("%d", &sm_lin);
        printf("Enter column length of second matrice -> ");
        scanf("%d", &sm_col);
    } while (fm_col != sm_lin); //Hope whoever uses it figures this out.

    dmatrice *first_matrice = make_matrice(fm_lin, fm_col);
    fill_matrice(first_matrice, fm_lin, fm_col, -1, 1);

    dmatrice *second_matrice = make_matrice(sm_lin, sm_col);
    fill_matrice(second_matrice, sm_lin, sm_col, -1, 1);

    dmatrice *product = matrice_multiplier(first_matrice, fm_lin, fm_col, second_matrice, sm_lin, sm_col);
    
    print_matrices(first_matrice, fm_lin, fm_col, second_matrice, sm_lin, sm_col, product);

    return 0;
}