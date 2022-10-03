
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                                                                                                                                                                                                                                           
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

int* vV;
int** caM;         // Matrix
int N, k;


int *getVector(int n)  {
 int *m;
 m = (int *)malloc(n * sizeof(int));
 if (!m){ fprintf(stderr,"Vector Memory error!\n");exit(-1);}
 return m;
}

int **getMatrix(int a, int b)  {
int i, **m;
    m = (int **) malloc((int)a*sizeof(int*));
    if (!m) { fprintf(stderr,"Matrix Memory error in step 1!\n"); exit(-1);}
    for (i = 0; i < a; i++) {
        m[i] = (int*) malloc((int)b*sizeof(int));
        if (!m[i])  { fprintf(stderr,"Matrix Memory error in step 2!\n"); exit(-1);}
    }
    return m;
}
void freeMemory(){
int i;
free(vV); vV=NULL;
for (i=0; i<N; i++) { free(caM[i]); caM[i]=NULL;        } free(caM);     caM=NULL;
}
int main (int argc, char *argv[ ]){
int i, j;
   k=10; N=20;
   vV=(int *) getVector(k);
   for (i=0; i<k; i++) vV[i]=i;
   for (i=0; i<k; i++) fprintf(stderr,"%d ", vV[i]);
   fprintf(stderr,"\n\n");
   caM=(int **) getMatrix(N,k);
   for (i=0; i<N; i++) for (j=0; j<k; j++) caM[i][j]=i+j;
   for (i=0; i<N; i++) {
       for (j=0; j<k; j++) fprintf(stderr,"%2d ", caM[i][j]);
       fprintf(stderr,"\n");
   }
   fprintf(stderr,"\n");
   freeMemory();
   return(0);
}
