/*
Q 3. WAP MPI Scatter (Collective Communications)
INPUT: sendbuf[4][4] = {
  {10.0, 20.0, 30.0, 40.0},
  {50.0, 60.0, 70.0, 80.0},
  {90.0, 100.0, 110.0, 120.0},
  {130.0, 140.0, 150.0, 160.0}  }
*/

#include<stdio.h>
#include<mpi.h>

void main(int argc,char *argv[])
{
    int sendbuff[4][4]= {
                        {10.0, 20.0, 30.0, 40.0},
                        {50.0, 60.0, 70.0, 80.0},
                        {90.0, 100.0, 110.0, 120.0},
                        {130.0, 140.0, 150.0, 160.0}};
    int recbuff[4],world_size,rank,i,j;
    int received[4][4]={{0}};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Scatter(sendbuff,4,MPI_INT,recbuff,4,MPI_INT,0,MPI_COMM_WORLD);

    for(i=0;i<world_size;i++)
        {
            printf("Scattering data %d from root to: %d \n",recbuff[i],rank);
        }

    MPI_Barrier(MPI_COMM_WORLD);

    for(i=0;i<world_size;i++)
    {
        recbuff[i]=recbuff[i]+200;
    }
    if(rank==world_size-1)
    {
        printf("\nScatter Complete.\n\n");
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Gather(recbuff,4,MPI_INT,received,4,MPI_INT,0,MPI_COMM_WORLD);

    for(i=0;i<world_size;i++)
        {
            printf("Gathering data %d from %d to root \n",recbuff[i],rank);
        }

    MPI_Barrier(MPI_COMM_WORLD);


    if(rank==0)
    {
        printf("\nGather Complete.\n\n");
    }
    
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();

}