# Introducción a la Programación Orientada a Objetos (UCSP)

Small C++ exercises from the *Introduction to Object-Oriented Programming*
course at Universidad Católica San Pablo (2016). All programs read from stdin.

| Program | Source | What it does |
|---|---|---|
| `lista` | `ListaSE/` | Singly linked list class (`nodo`, `lista`): reads `n` and `n` integers, prints each by index, then the whole list. |
| `abeja` | `Practica/ProblemaAbeja.cpp` | "Bee problem": number of closed walks of length `n` on a hexagonal grid that return to the start cell (dynamic programming). |
| `fiboLog` | `Practica/fiboLog.cpp` | Fibonacci by fast matrix exponentiation on 2096-bit integers (ttmath). Its output line is commented out in the original, so it computes but prints nothing. |

## Build

Requires `g++` and `make`.

```bash
make                       # builds build/lista and build/abeja
make fibo TTMATH_DIR=/path/to/ttmath-0.9.3   # optional; needs the header-only ttmath library
```

## Run

```bash
$ echo "5 3 1 4 1 5" | build/lista
3
1
4
1
5
3 1 4 1 5

$ echo 4 | build/abeja
90
$ echo 5 | build/abeja
360
```

## Layout

```
ListaSE/    linked list (lista.h + main.cc)
Practica/   bee problem and fast Fibonacci
Makefile    builds everything into build/
```
