#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define N 11

int verifica_vizinho(int mat[N][N],int i,int j) {
    int count = 0;
    return count = (mat[i-1][j-1] + mat[i-1][j] + mat[i-1][j+1] + mat[i][j-1] + mat[i][j+1] + mat[i+1][j-1] + mat[i+1][j] + mat[i+1][j+1]);
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
    int block_size = 2;
    for (int i = 0; i <N; i++) {
        for(int j = 0; j <N;j++) {
            if(i==0 || j==N-1 || j==0 || i==N-1)
                mat[i][j] = 0;
            else
                mat[i][j]=rand()%2;
        }
    }
    printf("mat inicial:\n");
    imprimir_mat(mat);
    int i,j,y,x,k,total_thread = 2;
    int n_process = N/total_thread;
    copia_mat(mat,mat2);
    omp_set_num_threads(total_thread);
    for(k = 0; k < 1;k++) {
        //printf("\nK MOMENTO:%d\n",k);
            for (i = 0; i < N-1; i+=block_size) {
                for(j = 0; j < N-1;j+=block_size) {
                    # pragma omp parallel for private (y,x)
                    for(y = 0; y < block_size; y++) {
                        for(x = 0; x < block_size; x++) {
                            int count = 0;
                            count = verifica_vizinho(mat,y,x);
                            //count-=mat[i][j];
                            if(mat[i+y][j+x]==1 && count < 2) {
                            mat2[i+y][j+x] = 0;
                            }          
                            else if(mat[i+y][j+x]==1 && count > 3) {
                                mat2[i+y][j+x] = 0;
                            }   
                            else if(mat[i+y][j+x]==0 && count==3) {
                                mat2[i+y][j+x]=1;
                            }
                            else {
                                mat2[i+y][j+x] = mat[i+y][j+x];
                            }
                        }
                        int ID = omp_get_thread_num();
                        printf("\nTHREAD ATUAL:%d\n",ID);
                        imprimir_mat(mat2);
                    }
                }     
            }
            copia_mat(mat2,mat);

        }   
        //imprimir_mat(mat2);

    printf("\nmat FINAL:\n");
    imprimir_mat(mat2);
}