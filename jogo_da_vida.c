#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define N 10

int verifica_vizinho(int mat[N][N],int i,int j) {
    int count = 0;

    if ( mat[i-1][j-1] == 1 && i-1 >= 0 && j-1 >= 0 ) {
        count++;
    }
    if ( mat[i-1][j] == 1 && i-1 >= 0 ) {
        count++;
    }
    if ( mat[i-1][j+1] == 1 && i-1 >= 0 && j+1 < N ) {
        count++;
    }
    if ( mat[i][j-1] == 1 && j-1 >= 0 ) {
        count++;
    }
    if ( mat[i][j+1] == 1 && j+1 < N ) {
        count++;
    }
    if ( mat[i+1][j-1] == 1 && j-1 >= 0 && i+1 < N ) {
        count++;
    }
    if ( mat[i+1][j] == 1 && i+1 < N ) {
        count++;
    }
    if ( mat[i+1][j+1] == 1  && i+1 < N && j+1 < N ) {
        count++;
    }
    return count;
}

void copia_mat(int mat[N][N], int mat2[N][N]) {

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            mat2[i][j]=mat[i][j];
        }
    }
}

void imprimir_mat(int mat2[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf(": %d ",mat2[i][j]);
        }
        printf("\n");
    }
}

void main() {

    int mat[N][N], mat2[N][N];
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N;j++) {
            mat[i][j]=rand()%2;
        }
    }
    printf("mat inicial:\n");
    imprimir_mat(mat);
    int i,j,l,m,k,total_thread = 2;
    int n_process = N/total_thread;
    copia_mat(mat,mat2);
    omp_set_num_threads(2);
    for(k = 0; k < 100;k++) {
        //printf("\nK MOMENTO:%d\n",k);
            # pragma omp parallel for private (i,j) schedule(static, n_process)
            for (i = 0; i < N; i++) {
                for(j = 0; j < N;j++) {
                    int count = 0;
                    count = verifica_vizinho(mat,i,j);
                    //count-=mat[i][j];
                    if(mat[i][j]==1 && count < 2) {
                        mat2[i][j] = 0;
                    }   
                    else if(mat[i][j]==1 && count > 3) {
                        mat2[i][j] = 0;
                    }   
                    else if(mat[i][j]==0 && count==3) {
                        mat2[i][j]=1;
                    }
                    else {
                        mat2[i][j] = mat[i][j];
                    }
                }
            int ID = omp_get_thread_num();
            printf("\nTHREAD ATUAL:%d\n",ID);
            imprimir_mat(mat2);     
            }
            copia_mat(mat2,mat);

        }   
        //imprimir_mat(mat2);

    printf("\nmat FINAL:\n");
    imprimir_mat(mat2);
}