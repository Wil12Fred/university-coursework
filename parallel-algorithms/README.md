# Algoritmos Paralelos

Exercises from the *Parallel Algorithms* course (UCSP, 2018): cache-aware matrix
multiplication, Pthreads (chapter 4 of P. Pacheco, *An Introduction to Parallel
Programming*), and two MPI programs. `PThreads/tarea.pdf` is the write-up
(in Spanish) reproducing the book's tables 4.1 and 4.3–4.5.

| Program | Source | What it does |
|---|---|---|
| `cache_matmul` | `Cache_MultiplicacionDeMatrices.cpp` | Naive vs. blocked 1002x1002 matrix multiplication; prints the time of each run |
| `pth_pi_busy2`, `pth_pi_mutex` | `PThreads/` | Estimate pi with threads; critical section by busy-waiting vs. a mutex |
| `pth_ll_one_mut`, `pth_ll_mult_mut`, `pth_ll_rwl` | `PThreads/` | Shared sorted linked list: one mutex for the list, one mutex per node, a read-write lock |
| `pth_mat_vect_rand_split` | `PThreads/` | Matrix-vector product with a random matrix split across threads |
| `oddevensort`, `mulmatrizvector` | `*.c` (MPI) | Odd-even transposition sort; matrix-vector product with `MPI_Scatter`/`MPI_Allgather` |

`PThreads/timer.h`, `PThreads/my_rand.h` and `PThreads/my_rand.c` are the
book's helper files, which were never committed; they are small compatible
re-implementations so the programs build.

## Build

```bash
make          # cache_matmul + all Pthreads programs into build/  (gcc, g++)
make mpi      # the MPI programs; needs mpicc (e.g. apt install libopenmpi-dev)
```

**The MPI programs were not built or run**: no MPI implementation was available
when this README was written.

## Run (real output)

```bash
$ build/pth_pi_busy2 4 100000000          # <threads> <terms>
With n = 100000000 terms,
   Multi-threaded estimate of pi  = 3.141592643589817
   Elapsed time = 3.895998e-02 seconds
   Single-threaded estimate of pi = 3.141592643589326
   Elapsed time = 9.439301e-02 seconds
   Math library estimate of pi    = 3.141592653589793

# <threads>; then: keys to insert, total ops, search fraction, insert fraction
$ printf '1000\n100000\n0.8\n0.1\n' | build/pth_ll_rwl 4
...
Inserted 1000 keys in empty list
Elapsed time = 1.362450e+00 seconds
Total ops = 100000
member ops = 80016
insert ops = 9952
delete ops = 10032

$ build/pth_mat_vect_rand_split 4 1000 1000   # <threads> <rows> <cols>
$ build/cache_matmul                          # 11 timings, ~2 s total

# MPI (unverified)
mpiexec -n 4 build/oddevensort
```

Timings depend on the machine.
