# algorithms-and-data-structures

[![CI](https://github.com/Wil12Fred/university-coursework/actions/workflows/algorithms-and-data-structures.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/algorithms-and-data-structures.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

C++ exercises from an algorithms and data structures course: sorting
algorithms with timing benchmarks (some of them multithreaded), hand-written
AVL, red-black and binary search trees, and a small ncurses game. Each folder
is independent.

## Features

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

## Requirements

- Debian/Ubuntu: `sudo apt install g++ make libncurses-dev`
- Arch: `sudo pacman -S gcc make ncurses`

The tests use AddressSanitizer and UBSan, which ship with GCC on both.

## Build

```bash
make           # every .cc with a main() -> build/<Folder>-<file>
make list      # show the program names
```

## Run

Real output:

```console
$ build/Tree-main
1
2
3
4
5
6
7
8
9
10

$ build/Heap-main          # seconds for n = 10, 100, ..., 10^6
2.39e-07
3.195e-06
4.4758e-05
0.000573145
0.00616003
0.0535829

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

`AVL-main` prints the tree in pre-order as `value depth`.

## Tests

```bash
make test
```

- `tests/unit_tests.cc` includes each program's source with `main` renamed and
  calls the real functions, compiled with AddressSanitizer and UBSan:
  - heapsort, quicksort, insertion, selection and bubble sort each sort empty,
    single, sorted, reversed, all-equal and random inputs (compared with
    `std::sort`), in exact-size buffers so any out-of-bounds access aborts;
  - the merge step of the bottom-up merge sort merges two sorted runs;
  - 2000 random AVL inserts/removes keep the tree a BST, height-balanced, with
    correct stored heights, and holding exactly the expected multiset;
  - 500 inserts and 300 deletes on the red-black tree keep the BST order, the
    parent pointers, no red node with a red child, and equal black heights.
- `tests/run_golden.sh` runs `Tree-main`, `AVL-main` and
  `TareaProblema-problema` on the inputs in `tests/golden/` and compares the
  output with the committed `.out` files.

The timing benchmarks print machine-dependent numbers and are not
golden-tested; their sort functions are covered by the unit tests instead.

## Project layout

```
Makefile              builds every program into build/; `make test`
<Folder>/main*.cc     one exercise per folder
RedBlack/rbtree.h     the red-black tree library
tests/unit_tests.cc   unit tests of the sorts and trees
tests/golden/         golden inputs and expected outputs
```

## Known limitations

- Quicksort (`Quick-main`, `Quick-main_`) used to read past the end of the
  array when the last elements equalled the pivot; fixed, and covered by the
  unit tests.
- `Merge-main` keeps two stack arrays of size `n`; very large `n` overflows the stack.
- The O(n²) sorts (`Insert-main`, `Burbuja-main_`) take a very long time at n = 10^6.
- The AVL tree never frees its nodes; `rbDelete` calls its `updateNode`
  callback without checking for null, so callers must pass a function.
- `TareaProblema-problema` always prints a 25-character grid, whatever the
  grid size.
- `Merge-main_1`, `Graph`, `HASH`, `Queue`, `Stack` are unfinished skeletons.

## Background

Written for an algorithms and data structures course at university, 2016–2018.

## License

MIT — see [LICENSE](../LICENSE).
