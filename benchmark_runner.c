#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rdcycle.h"

extern void naive_matmul(int n);
extern void cacheAware_matmul(int n, int TILE_SIZE);

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <N> <TILE_SIZE> <mode>\n", argv[0]);
        printf("mode = 0 for naive, 1 for cache-aware\n");
        return 1;
    }

    int N = atoi(argv[1]);
    int TILE_SIZE = atoi(argv[2]);

    unsigned long long start, end, naive_cycles, cache_aware_cycles;

    printf("\n\n\n -----------------MATRICES-----------------\n\n");

    printf("Running naive matrix multiplication...\n");
    start = rdcycle();
    naive_matmul(N);
    end = rdcycle();
    naive_cycles = end - start;
    
    printf("Running cache-aware matrix multiplication with TILE_SIZE = %d...\n", TILE_SIZE);
    start = rdcycle();
    cacheAware_matmul(N, TILE_SIZE);
    end = rdcycle();
    cache_aware_cycles = end - start;

    printf("\n\n\n -----------------RESULT-----------------\n\n");

    printf("Cache-aware matmul cycles: %llu\n", cache_aware_cycles);
    printf("Naive matmul cycles: %llu\n", naive_cycles);
    printf("Difference in cycles: %llu\n", abs((long long)(naive_cycles - cache_aware_cycles)));

    if (naive_cycles > cache_aware_cycles) {
        printf("Cache-aware matrix multiplication is faster by %llu cycles.\n", abs((long long)(naive_cycles - cache_aware_cycles)));
    } else {
        printf("Naive matrix multiplication is faster by %llu cycles.\n", abs((long long)(cache_aware_cycles-naive_cycles)));
    }   
    return 0;
}