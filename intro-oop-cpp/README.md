# intro-oop-cpp

[![CI](https://github.com/Wil12Fred/university-coursework/actions/workflows/intro-oop-cpp.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/intro-oop-cpp.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

Small C++ exercises from an introduction to object-oriented programming
course: a singly linked list class, a dynamic-programming count of closed
walks on a hexagonal grid, and Fibonacci by fast matrix exponentiation on
2096-bit integers. All programs read from stdin.

## Features

| Program | Source | What it does |
|---|---|---|
| `lista` | `ListaSE/` | Singly linked list class (`nodo`, `lista`): reads `n` and `n` integers, prints each by index, then the whole list. |
| `abeja` | `Practica/ProblemaAbeja.cpp` | "Bee problem": number of closed walks of length `n` on a hexagonal grid that return to the start cell (dynamic programming; OEIS A002898). |
| `fiboLog` | `Practica/fiboLog.cpp` | The `n`-th Fibonacci number by fast matrix exponentiation (O(log n) multiplications) on 2096-bit unsigned integers from the header-only [ttmath](https://www.ttmath.org/) library. |

## Requirements

- Debian/Ubuntu: `sudo apt install g++ make`
- Arch: `sudo pacman -S gcc make`

ttmath 0.9.3 (BSD-3-Clause, header-only) is vendored in `third_party/`, so
nothing else is needed.

## Build

```bash
make            # build/lista, build/abeja, build/fiboLog
```

## Run

Real output:

```console
$ echo "5 3 1 4 1 5" | build/lista
3
1
4
1
5
3 1 4 1 5

$ echo 4 | build/abeja
90

$ echo 100 | build/fiboLog
354224848179261915075
```

## Tests

```bash
make test
```

`tests/run_golden.sh` feeds each `tests/golden/<program>.<case>.in` to the
program and compares stdout with `<case>.out`. The expected values come from
independent references, not from the programs themselves:

- `abeja`, n = 0 … 10: the terms of OEIS A002898 (1, 0, 6, 12, 90, 360, …);
- `fiboLog`, n = 0, 1, 2, 10, 93, 100, 300, 2000: Fibonacci numbers computed
  with Python's arbitrary-precision integers (F(2000) has 1388 bits, so it
  exercises the big-number arithmetic);
- `lista`: empty, single-element and five-element lists.

## Project layout

```
ListaSE/                     linked list (lista.h + main.cc)
Practica/ProblemaAbeja.cpp   bee problem
Practica/fiboLog.cpp         fast Fibonacci
third_party/ttmath-0.9.3/    vendored ttmath headers and their license
tests/                       golden inputs/outputs and the runner
Makefile                     builds everything into build/; `make test`
```

## Known limitations

- `fiboLog`'s print statement was commented out in the original, so it
  computed and printed nothing; it is restored. It also answered 1 for n = 0;
  fixed (F(0) = 0).
- `fiboLog` overflows silently once F(n) needs more than 2096 bits (n ≈ 3020).
- `abeja` uses 64-bit counters; the count grows roughly like 6^n (n = 30 is
  already 5.5·10^18), so it overflows silently a little beyond that.
- `lista` never frees its nodes.

## Background

Written for an introduction to object-oriented programming course at
university, 2016.

## License

MIT — see [LICENSE](../LICENSE). `third_party/ttmath-0.9.3/` keeps its own
BSD-3-Clause license (`third_party/ttmath-0.9.3/COPYRIGHT`).
