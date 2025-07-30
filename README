# RISC-V Matrix Multiplication Benchmarking

This project benchmarks matrix multiplication on RISC-V using naive and cache-aware (loop-tiled) methods, running in a simulated environment (spike + pk). It measures execution time in CPU cycles using `rdcycle`.


## Requirements

You must have the following installed:

1. riscv64-linux-gnu-gcc
2. spike
3. pk (Proxy kernel)
4. make (build automation)

## Terminal Commands to Run Everything

```bash
cd /path/to/your/project
make
make run
make clean
```
or if you want to run with specific parameters, then run 
```bash
make run N=10 TILE=2
```
---
## Sample Output

```
Cache-aware matmul cycles: 378168
Naive matmul cycles: 382324
Difference in cycles: 4156
Cache-aware matrix multiplication is faster by 4156 cycles.
```
---
