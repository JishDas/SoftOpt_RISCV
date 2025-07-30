#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

extern void init_matrix (int *matrix, int n);
extern void zero_matrix (int *matrix, int n);

void cacheAware_matmul(int n, int TILE_SIZE) {

    // init matrices A, B, C
    int* A = malloc(sizeof(int) * n * n);
    int* B = malloc(sizeof(int) * n * n);
    int* C = malloc(sizeof(int) * n * n);

    srand(0);
    init_matrix(A, n);
    init_matrix(B, n);
    zero_matrix(C, n);

    // cache-aware matrix multiplication
    for (int ii = 0; ii < n; ii += TILE_SIZE) {
    for (int jj = 0; jj < n; jj += TILE_SIZE) {
        for (int kk = 0; kk < n; kk += TILE_SIZE) {
            // Work on small 'TILE_SIZE' blocks of the matrix at a time
            for (int i = ii; i < min(ii + TILE_SIZE, n); i++)
                for (int j = jj; j < min(jj + TILE_SIZE, n); j++)
                    for (int k = kk; k < min(kk + TILE_SIZE, n); k++)
                        C[i*n + j] += A[i*n + k] * B[k*n + j];
        }
    }
    }


    //print out
    printf("Matrix A:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", A[i*n + j]);
        }
        printf("\n");
    }

    printf("Matrix B:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", B[i*n + j]);
        }
        printf("\n");
    }

    printf("Resulting matrix C:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", C[i*n + j]);
        }
        printf("\n");
    }

    // Free allocated memory
    free(A);
    free(B);
    free(C);
}

// if you want to run the code separately, then uncomment and run
// int main(int argc, char *argv[]) {

//     if (argc < 3) {
//         printf("Usage: %s <N> <BLOCK_SIZE>\n", argv[0]);
//         return 1;
//     }

//     int n = atoi(argv[1]);
//     int TILE_SIZE = atoi(argv[2]);

//     cacheAware_matmul(n, TILE_SIZE);
//     return 0;
// }