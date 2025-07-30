# Makefile for RISC-V matrix multiplication benchmark using QEMU + PK
# All outputs (object files and binary) go into out/

# Compiler and flags
RISCV_GCC = riscv64-unknown-elf-gcc
CFLAGS = -O3
SPIKE = spike
# PK = /home/jishnu/projects/riscv/shakti/shakti-tools/riscv64/riscv64-unknown-elf/bin/pk
PK = pk

# Directories
OUT_DIR = out
SRC_DIR = .
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SOURCES))
EXEC = $(OUT_DIR)/benchmark.out

# Default parameters (can override via make run N=... TILE=... MODE=...)
N ?= 10
TILE ?= 2

# Target: all
all: $(OUT_DIR) $(EXEC)

# Create output directory if not exists
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Compile each .c to out/*.o
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	$(RISCV_GCC) $(CFLAGS) -c $< -o $@

# Link all object files into final executable
$(EXEC): $(OBJECTS)
	$(RISCV_GCC) $(CFLAGS) -o $(EXEC) $(OBJECTS)

# Run using spike and pk
run: all
	$(SPIKE) $(PK) ./$(EXEC) $(N) $(TILE) $(MODE)

# Clean build artifacts
clean:
	rm -rf $(OUT_DIR)

.PHONY: all run clean