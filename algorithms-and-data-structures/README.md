# Algoritmos y Estructuras de Datos (UCSP)

C++ exercises from the *Algorithms and Data Structures* course at Universidad
Católica San Pablo (2016–2018): sorting algorithms with timing benchmarks
(some of them multithreaded), hand-written data structures, and a small
ncurses game. Each folder is independent.

| Folder | Program(s) | What it is |
|---|---|---|
| `Burbuja/` | `Burbuja-main`, `Burbuja-main_` | Bubble sort: threaded (reads `n`) and sequential benchmark for n = 10 … 10^6 |
| `Insert/` | `Insert-main` | Insertion sort benchmark |
| `Select/` | `Select-main` | Selection sort benchmark |
| `Merge/` | `Merge-main`, `Merge-main_`, `Merge-main_1` | Bottom-up merge sort: threaded (reads `n` and thread count), sequential benchmark, unfinished variant |
| `Quick/` | `Quick-main`, `Quick-main_` | Quicksort: threaded (reads `n`) and sequential benchmark |
| `Heap/` | `Heap-main` | Heapsort benchmark |
| `Estupid/` | `Estupid-main` | "Stupid sort": random parallel swaps until sorted (reads `n`; keep it small) |
| `AVL/` | `AVL-main`, `AVL-array_avl` | AVL tree with insert/remove (interactive menu); array of AVL trees |
| `RedBlack/` | `RedBlack-main` | Red-black tree library (`rbtree.h`); `main` only constructs one |
| `Tree/` | `Tree-main` | Binary search tree with an in-order iterator |
| `Graph/`, `HASH/`, `Queue/`, `Stack/` | | Skeletons (graph, hash table, queue, stack); their `main` does nothing visible |
| `TareaProblema/` | `TareaProblema-problema` | Brute force over bitmasks: fewest cell flips so every row and every column of a 0/1 grid has the same count |
| `Bomb/` | `Bomb-main` | ncurses game: a linked list of countdown bombs you defuse with the arrow keys |

The benchmarks print one elapsed time in seconds per input size, so the numbers
vary by machine. The O(n²) sorts (`Insert-main`, `Burbuja-main_`) take a very
long time at n = 10^6.

## Build

Requires `g++` (C++17), `make` and ncurses headers (for `Bomb`).

```bash
make           # every .cc with a main() -> build/<Folder>-<file>
make list      # show the program names
```

## Run (real output)

```bash
$ build/Tree-main
1
2
...
10

$ build/Heap-main          # seconds for n = 10, 100, ..., 10^6
2.62e-07
3.224e-06
4.4165e-05
0.000567674
0.00615991
0.0566601

$ printf '1\n5\n3 1 4 1 5\n2\n3\n' | build/AVL-main   # insert 5 values, then remove 3
insert-remove
3 0
1 1
1 2
4 1
5 2
insert-remove
4 0
1 1
1 2
5 1
insert-remove

$ printf '2 3\n100\n001\n' | build/TareaProblema-problema
2
0000000000000000000000000

$ build/Bomb-main          # needs a real terminal
```

## Known issues

- `Merge-main` keeps two stack arrays of size `n`; very large `n` overflows the stack.
- `Merge-main_1`, `Graph`, `HASH`, `Queue`, `Stack` are unfinished skeletons.
