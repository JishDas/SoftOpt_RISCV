# Makefile for RISC-V Matrix Multiplication using Spike + pk
# Builds separate non-vector and vector benchmarks in separate directories

# Toolchain
RISCV_GCC = riscv64-unknown-elf-gcc
SPIKE = spike
# PK = pk
PK = /home/jishnu/projects/riscv/shakti/shakti-tools/riscv64/riscv64-unknown-elf/bin/pk

# Directories
SRC_DIR = .
OUT_DIR = out
NONVEC_DIR = $(OUT_DIR)/nonvec
VEC_DIR = $(OUT_DIR)/vec

# Source files
VECTOR_RUNNER_SRC = $(SRC_DIR)/benchmark_runner_vector.c
COMMON_SOURCES = $(SRC_DIR)/naive_matmul.c $(SRC_DIR)/cacheAware_matmul.c
NONVEC_RUNNER_SRC = $(SRC_DIR)/benchmark_runner.c

# Object files
NONVEC_OBJECTS = \
	$(NONVEC_DIR)/naive_matmul.o \
	$(NONVEC_DIR)/cacheAware_matmul.o \
	$(NONVEC_DIR)/benchmark_runner.o

VEC_OBJECTS = \
	$(VEC_DIR)/naive_matmul.o \
	$(VEC_DIR)/cacheAware_matmul.o \
	$(VEC_DIR)/benchmark_runner_vector.o

# Executables
NONVEC_EXEC = $(NONVEC_DIR)/benchmark.out
VEC_EXEC = $(VEC_DIR)/benchmark_vector.out

# Compilation flags
CFLAGS_NONVEC = -O3 -march=rv64gc -mabi=lp64d
CFLAGS_VEC = -O3 -march=rv64gcv -mabi=lp64d

# Runtime parameters
N ?= 10
TILE ?= 2

# Create output directories
$(NONVEC_DIR):
	mkdir -p $(NONVEC_DIR)

$(VEC_DIR):
	mkdir -p $(VEC_DIR)

# Default target
all: $(NONVEC_DIR) $(VEC_DIR) $(NONVEC_EXEC) $(VEC_EXEC)

# Compile non-vector sources
$(NONVEC_DIR)/%.o: $(SRC_DIR)/%.c
	$(RISCV_GCC) $(CFLAGS_NONVEC) -c $< -o $@

# Compile vector sources
$(VEC_DIR)/%.o: $(SRC_DIR)/%.c
	$(RISCV_GCC) $(CFLAGS_VEC) -c $< -o $@

# Link non-vector executable
$(NONVEC_EXEC): $(NONVEC_OBJECTS)
	$(RISCV_GCC) $(CFLAGS_NONVEC) -o $@ $^

# Link vector executable
$(VEC_EXEC): $(VEC_OBJECTS)
	$(RISCV_GCC) $(CFLAGS_VEC) -o $@ $^

# Run non-vector
run: $(NONVEC_EXEC)
	$(SPIKE) $(PK) ./$< $(N) $(TILE)

# Run vector
run-vector: $(VEC_EXEC)
	$(SPIKE) $(PK) ./$< $(N) $(TILE)

# Clean all
clean:
	rm -rf $(OUT_DIR)

.PHONY: all run run-vector clean