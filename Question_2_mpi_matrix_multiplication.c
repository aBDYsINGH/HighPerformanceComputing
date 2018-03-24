/*
Q2.Write any serial program convert that to openMP, to MPI program.
This program is serial matrix multiplication.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int **matrix_generator(int row,int col);
int **multiply_matrices(int **matrix_A,int **matrix_B,int rowsA, int colsA,int rowsB,int colsB);
void display_matrix(int **matrixA,int cols,int rows);

int main(int argc,char *argv[])
{
    srand(time(0));

    int **matrix_A,**matrix_B,**matrix_result,rowsA,colsA,rowsB,colsB,world_rank,world_size;
    
    rowsA = atoi(argv[1]);
    colsA = atoi(argv[2]);
    rowsB = atoi(argv[3]);
    colsB = atoi(argv[4]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    

/*
    int *matrix_AA = malloc(sizeof(int*)*rowsA),*temp_matrix = malloc(sizeof(int*)*rowsA*colsA/world_size);
    matrix_AA = 0;
    temp_matrix = 0;
*/
    if (argc != 5)
    {
        fprintf(stderr,"Usage: mpirun -np <No. of processors> ./a.out <Rows A> <Columns A> <Rows B> <Columns B>\n");
        exit(-1);
    }
    else if(colsA != rowsB)
    {
        printf("Check the dimensions of the matrices!\n\n");
    }

/*
    printf("Enter the dimensions of Matrix A:\n");
    scanf("%d%d",&rowsA,&colsA);
    printf("Enter the dimensions of Matrix B:\n");
    scanf("%d%d",&rowsB,&colsB);
    printf("\n\n");
*/

        matrix_A = matrix_generator(rowsA,colsA);
        matrix_B = matrix_generator(rowsB,colsB);

        if(myrank==0)
        {
            MPI_Scatter (&matrix_A[0][0], SIZE*SIZE/P, MPI_INT, &matrix_A, SIZE*SIZE/P, MPI_INT, 0, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Scatter (&matrix_A[0][0], SIZE*SIZE/P, MPI_INT, &matrix_A[0][0], SIZE*SIZE/P, MPI_INT, 0, MPI_COMM_WORLD);
        }

        MPI_Bcast(matrix_B, rowsB*colsB , MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Barrier(MPI_COMM_WORLD);

        printf("Scatter complete");

        matrix_result = multiply_matrices(matrix_A,matrix_B,rowsA,colsA,rowsB,colsB);

        if(myrank==0)
        {
            MPI_Gather (MPI_IN_PLACE, SIZE/P, MPI_INT, &matrix_result[0][0], SIZE/P, MPI_INT, 0, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Gather (&matrix_result[from][0], SIZE/P, MPI_INT, &matrix_result[0][0], SIZE/P, MPI_INT, 0, MPI_COMM_WORLD);
        }
        MPI_Barrier(MPI_COMM_WORLD);

        printf("Gather Complete");

    if (world_rank == 0)
    {
        printf("Matrix A:\n");
        display_matrix(matrix_A,rowsA,colsA);
        printf("\n\n");

        printf("Matrix B:\n");
        display_matrix(matrix_B,rowsB,colsB);
        printf("\n\n");

        display_matrix(matrix_result,rowsA,colsB);
    }
    return 0;
    MPI_Finalize();
    
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
