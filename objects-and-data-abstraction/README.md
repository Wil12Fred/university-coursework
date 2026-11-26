# Objetos y Abstracción de Datos

C++ exercises from the *Objects and Data Abstraction* course (UCSP, 2016–2018).
Small, independent programs; most are interactive.

| Program | Source | What it does |
|---|---|---|
| `game` | `GameNcurses/` | Terminal arcade game (ncurses): a tank (`a`) at the bottom shoots (`*`) at a snake (`o`) that zig-zags down the board. Shooting the body splits the snake; hitting the head wins, the snake reaching the tank ends the game. |
| `curses-hello` | `GameNcurses/pr.cc` | Minimal ncurses input/output test. |
| `puzzle` | `Puzzle/` | 15-puzzle on a 4x4 board (`Puzzle` class). Shuffles the board and moves the gap with `w`/`s`/`a`/`d` until solved. |
| `euclides` | `EuclidesExtendido/ext.cc` | Extended Euclid + modular inverse + a multiplicative byte cipher for files. Unfinished: `main` only asks for a user name and key; the encryption routine (`revisar`) is commented out. |
| `lista-doble` | `ListaDoblementeEnlazada/` | Empty starting stub for a doubly linked list (template node only). |

## Build

Requires `g++`, `make` and the ncurses development headers.

```bash
make            # builds every program into build/
```

## Run

```bash
# Game: reads the board size and the snake length, then needs a real terminal.
# Left/right arrows move the tank, space shoots.
build/game                # then type: 15 4 <Enter>

# 15-puzzle (input can be piped; it stops at end of input)
$ printf 'w\nd\n' | build/puzzle
1 2 3 4
5 6 7 8
9 A B C
D E F

8 5 E C          <- shuffled board (random)
...
```

## Layout

```
GameNcurses/              game: snake, bullet, tank and game classes (header-only) + main.cc
Puzzle/                   15-puzzle class
EuclidesExtendido/        extended Euclid / modular inverse
ListaDoblementeEnlazada/  doubly linked list stub
```
