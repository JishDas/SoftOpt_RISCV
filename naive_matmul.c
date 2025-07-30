#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void init_matrix(int *matrix, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i * n + j] = rand() % 10; // Random values between 0 and 9
}

void zero_matrix(int *matrix, int n) {
    for (int i = 0; i < n * n; i++) {
        matrix[i] = 0;
    }
}

void naive_matmul(int n){

    //init matrices A, B, C
    int* A = malloc(sizeof(int) * n * n);
    int* B = malloc(sizeof(int) * n * n);
    int* C = malloc(sizeof(int) * n * n);

    srand(0);
    init_matrix(A, n);
    init_matrix(B, n);
    zero_matrix(C, n);

    //normal interative matrix multiplication
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
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

//     if (argc < 2) {
//         printf("Usage: %s <N> <BLOCK_SIZE>\n", argv[0]);
//         return 1;
//     }

//     int n = atoi(argv[1]);
//     naive_matmul(n);

//     return 0;
// }