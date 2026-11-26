CC       ?= gcc
CXX      ?= g++
MPICC    ?= mpicc
CFLAGS   ?= -O2 -Wall
CXXFLAGS ?= -O2 -Wall
BUILD    := build

PTH_SIMPLE := pth_pi_busy2 pth_pi_mutex pth_mat_vect_rand_split
PTH_LIST   := pth_ll_one_mut pth_ll_mult_mut pth_ll_rwl
MPI_PROGS  := mulmatrizvector oddevensort

.PHONY: all mpi clean
all: $(BUILD)/cache_matmul $(addprefix $(BUILD)/,$(PTH_SIMPLE) $(PTH_LIST))

# MPI programs need an MPI implementation (e.g. apt install libopenmpi-dev).
mpi: $(addprefix $(BUILD)/,$(MPI_PROGS))

$(BUILD):
	mkdir -p $@

$(BUILD)/cache_matmul: Cache_MultiplicacionDeMatrices.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(addprefix $(BUILD)/,$(PTH_SIMPLE)): $(BUILD)/%: PThreads/%.c PThreads/timer.h | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $< -lpthread -lm

$(addprefix $(BUILD)/,$(PTH_LIST)): $(BUILD)/%: PThreads/%.c PThreads/my_rand.c PThreads/my_rand.h PThreads/timer.h | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $< PThreads/my_rand.c -lpthread

$(addprefix $(BUILD)/,$(MPI_PROGS)): $(BUILD)/%: %.c | $(BUILD)
	$(MPICC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BUILD)
