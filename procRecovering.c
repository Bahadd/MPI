#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define TAILLE_MAX 3
#define MAX_NEIGHBOURS 7
void showNeighbours(int *vect, int length){
  int i;
  for(i=0; i< length; i++){
    printf("%d \t" , vect[i]);
  }
}

char ** readFile(FILE * file , int maxLines){
  file = fopen("fileNetwork.txt" , "r");
  int i;
  char ** lines = malloc(maxLines*sizeof(char *));
  for(i=0; i< maxLines; i++)
  {
    lines[i] = malloc(TAILLE_MAX*sizeof(char));
  }

  char * tstLine = NULL;
  size_t len=0;
  ssize_t read;
  i=0;
    while((read = getline(&tstLine , &len, file)) != -1 ){
       printf("Retrieved line of length %zu:\n", read);
       printf("%s", tstLine);
       (lines[i])[0] = tstLine[0];
       (lines[i])[1] = tstLine[1];
       (lines[i])[2] = tstLine[2];
       i+=1;
     }
    // printf("\n");
  return lines;

}

void displayIntVector(int * vector, int length){
  int i;
  for(i=0; i< length; i++){
    printf("%d \t", vector[i]);
  }
  printf("\n");
}

int * discoverNeighbourhood(char  process, char ** lines , int maxLines){
  char  temp []= "-:";
  temp[0] = process;
  temp[1] = ':';
  int i,ind, * neighbours = malloc(MAX_NEIGHBOURS*sizeof(int));
  printf("J'affiche le temp  %s \n", temp);
  for(i=0; i< maxLines; i++){
    printf("line i0 = %c et line i1 = %c \n", (lines[i])[0],(lines[i])[1]);
    if(temp[0] == (lines[i])[0] && temp[1] == (lines[i])[1]){
      printf("%s  =  %s  \n", temp , lines[i]);
      ind = i+1;
      i=1;
      while ((lines[ind])[1] != ':' && (lines[ind])[0] != '-') {
        neighbours[i] = (lines[ind])[0] -'0';
        ind+=1;
        i+=1;
      }
      neighbours[0] = i-1;
      break;
    }

  }


  return neighbours;
}



int main(int argc, char *argv[]) {
  printf("Je suis executé par le root \n");
  FILE * file;

  int maxLines = MAX_NEIGHBOURS*(MAX_NEIGHBOURS-1)/2;
  char ** lines = readFile(file, maxLines);


  int rank, size, newsize;

  MPI_Init(&argc, &argv);

      MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    	MPI_Comm_size(MPI_COMM_WORLD,&size);


      char tmp[2];
      sprintf(tmp, "%d" , rank);
      char process = tmp[0];
      int * neighbours = discoverNeighbourhood(process , lines, maxLines);

      displayIntVector(neighbours , MAX_NEIGHBOURS);

      MPI_Comm  worlds;

      int nodes = 1;
      int * sources = malloc(sizeof(int));
      sources[0]=rank;
      int * degrees = malloc(sizeof(int));
      degrees[0]= neighbours[0];
      int i;
      int  *destination = malloc(degrees[0]*sizeof(int));
      int * weight = malloc(degrees[0]*sizeof(int));
      for(i = 1; i< (degrees[0])+1; i++){
        destination[i-1] = neighbours[i];
        weight[i-1] = 0;
        printf("destination = %d \n" , destination[i-1]);
      }
      int reorder = 1;


      printf("avant de lancer\n");
      printf("mon noeud est %d \n ma source est %d \n mon degre est %d \n et mes destinations \n", nodes, sources[0], degrees[0]);
      for(i=0; i< degrees[0]; i++){
        printf("%d \n", destination[i]);
      }

      
      MPI_Dist_graph_create(MPI_COMM_WORLD , nodes, sources, degrees, destination, weight, MPI_INFO_NULL,reorder, &worlds);

      MPI_Comm_size(worlds,&newsize);
      printf("the size is %d and the fucking rank is %d \n" , newsize, rank);
      int data= rank;
      MPI_Bcast(&data, 1, MPI_INT, 0, worlds);
      printf("Je suis %d et j'ai reçu %d \n",rank, data );






  MPI_Finalize();
  return 0;
}
