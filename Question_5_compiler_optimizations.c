/*
Q. 5 Write any program and apply compiler optimization options (-O1, -O2, -O3 ) and note down timings (apply same dataset)

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function declarations
int **matrix_generator(int row,int col);
int **multiply_matrices(int **matrix_A,int **matrix_B,int rowsA, int colsA,int rowsB,int colsB);
void display_matrix(int **matrixA,int cols,int rows);

//main function
void main(int argc,char *argv[])
{
        // create double pointers for the matrices to keep the matrices dynamic.
    int **matrix_A,**matrix_B,**matrix_result,rowsA,colsA,rowsB,colsB;

    rowsA = atoi(argv[1]);
    colsA = atoi(argv[2]);
    rowsB = atoi(argv[3]);
    colsB = atoi(argv[4]);

//    printf("Enter the dimensions of Matrix A:\n");
//    scanf("%d%d",&rowsA,&colsA);
//    printf("Enter the dimensions of Matrix B:\n");
//    scanf("%d%d",&rowsB,&colsB);
//    printf("\n\n");

    if(colsA!=rowsB)
    {
        printf("Check the dimensions of the matrices!\n");
        exit(-1);
    }
    else
    {
        //seed the rand() function once.
    	srand(time(0));
        //call matrix_generator function twice to generate 2 random matrices.
    	matrix_A = matrix_generator(rowsA,colsA);
        matrix_B = matrix_generator(rowsB,colsB);
        //call the multiply_matrices to multiply the two random matrices.
        matrix_result = multiply_matrices(matrix_A,matrix_B,rowsA,colsA,rowsB,colsB);
//print the matrices and the result.
/*
	printf("Matrix A:\n");
        display_matrix(matrix_A,rowsA,colsA);
        printf("\n\n");

        printf("Matrix B:\n");
        display_matrix(matrix_B,rowsB,colsB);
        printf("\n\n");

        display_matrix(matrix_result,rowsA,colsB);
*/
    }
}

//matrix_generator function returns double pointer.
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

//multiply_matrices function returns double pointer.
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

//display_matrix function is used to display the result.
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


/*
OUTPUT: 
abdy@abdy-linux:~/Documents/M.Tech/HighPerformanceComputing$ gcc -O1 Question_2_serial_matrix_multiplication.c
abdy@abdy-linux:~/Documents/M.Tech/HighPerformanceComputing$ time ./a.out 1000 1000 1000 1000
real    0m2.465s
user    0m2.449
ssys     0m0.016s
abdy@abdy-linux:~/Documents/M.Tech/HighPerformanceComputing$ gcc -O2 Question_2_serial_matrix_multiplication.c
abdy@abdy-linux:~/Documents/M.Tech/HighPerformanceComputing$ time ./a.out 1000 1000 1000 1000
real    0m1.558s
user    0m1.545s
sys     0m0.013s
abdy@abdy-linux:~/Documents/M.Tech/HighPerformanceComputing$ gcc -O3 Question_2_serial_matrix_multiplication.c
abdy@abdy-linux:~/Documents/M.Tech/HighPerformanceComputing$ time ./a.out 1000 1000 1000 1000
real    0m1.506s
user    0m1.498s
sys     0m0.008s
abdy@abdy-linux:~/Documents/M.Tech/HighPerformanceComputing$
*/