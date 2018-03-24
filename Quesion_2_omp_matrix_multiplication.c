/*
Q2.Write any serial program convert that to openMP, to MPI program.
This program is OpenMP matrix multiplication.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int **matrix_generator(int row,int col);
int **multiply_matrices(int **matrix_A,int **matrix_B,int rowsA, int colsA,int rowsB,int colsB);
void display_result(int **matrix,int cols,int rows);
void display_matrix(int **matrixA,int cols,int rows);

void main()
{
    srand(time(0));

    int **matrix_A,**matrix_B,**matrix_result,rowsA,colsA,rowsB,colsB,tid;
    tid = omp_get_thread_num();
        printf("Enter the dimensions of Matrix A:\n");
        scanf("%d%d",&rowsA,&colsA);
        printf("Enter the dimensions of Matrix B:\n");
        scanf("%d%d",&rowsB,&colsB);
        printf("\n\n");

        if(colsA!=rowsB)
        {
            printf("Check the dimensions of the matrices!\n");
            exit(-1);      
        }
        else
        {   
            if(tid == 0)
            {
                matrix_A = matrix_generator(rowsA,colsA);
                matrix_B = matrix_generator(rowsB,colsB);
            }
            #pragma omp parallel
            {
                matrix_result = multiply_matrices(matrix_A,matrix_B,rowsA,colsA,rowsB,colsB);
            }
            if(tid == 0)
            {
                printf("Matrix A:\n");
                display_matrix(matrix_A,rowsA,colsA);
                printf("\n\n");

                printf("Matrix B:\n");
                display_matrix(matrix_B,rowsB,colsB);
                printf("\n\n");

                display_matrix(matrix_result,rowsA,colsB);
            }
    }
}

int **matrix_generator(int row, int col)
{
    int i, j, **intMatrix;

    intMatrix = (int **)malloc(sizeof(int *) * row); 

    for (i = 0; i < row; i++)
    {
        intMatrix[i] = (int *)malloc(sizeof(int *) * col);
        for (j = 0;j<col;j++)
        {
            intMatrix[i][j]=rand()%10;
        }
    }
    return intMatrix;
}

int **multiply_matrices(int **matrix_A,int **matrix_B,int rowsA, int colsA,int rowsB,int colsB)
{
    int i, j, k, **resMatrix;

    resMatrix = (int **)malloc(sizeof(int *) * rowsB); 

    for (i = 0; i < rowsA; i++)
    {
        resMatrix[i] = (int *)malloc(sizeof(int *) * colsB);
        for (j = 0;j<colsB;j++)
        {
            resMatrix[i][j] = 0;
            for (k = 0; k < rowsB; k++)                
                resMatrix[i][j] = resMatrix[i][j] + matrix_A[i][k] * matrix_B[k][j];        
        }
    }
    return resMatrix;
}

void display_matrix(int **matrix, int rows,int cols)
{
    int i,j;
    for (i = 0; i < rows; i = i + 1)
	{
		for (j = 0; j < cols; j = j + 1)
            printf("%d ",matrix[i][j]);
		printf("\n");
	}        
}
