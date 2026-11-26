# objects-and-data-abstraction

[![CI](https://github.com/Wil12Fred/university-coursework/actions/workflows/objects-and-data-abstraction.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/objects-and-data-abstraction.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

C++ exercises from an objects and data abstraction course: a terminal arcade
game built from small classes on ncurses, a 15-puzzle class, and extended
Euclid with a modular-inverse byte cipher. Small, independent programs; most
are interactive.

## Features

| Program | Source | What it does |
|---|---|---|
| `game` | `GameNcurses/` | Terminal arcade game (ncurses): a tank (`a`) at the bottom shoots (`*`) at a snake (`o`) that zig-zags down the board. Shooting the body splits the snake; hitting the head wins, the snake reaching the tank ends the game. |
| `curses-hello` | `GameNcurses/pr.cc` | Minimal ncurses input/output test. |
| `puzzle` | `Puzzle/` | 15-puzzle on a 4x4 board (`Puzzle` class). Shuffles the board and moves the gap with `w`/`s`/`a`/`d` until solved. |
| `euclides` | `EuclidesExtendido/ext.cc` | Extended Euclid, modular inverse and a multiplicative byte cipher for files. Unfinished: `main` only asks for a user name and key; the file encryption (`revisar`) is commented out. |
| `lista-doble` | `ListaDoblementeEnlazada/` | Empty starting stub for a doubly linked list (template node only). |

## Requirements

- Debian/Ubuntu: `sudo apt install g++ make libncurses-dev` (`script` from
  `bsdutils` is used by the game's smoke test)
- Arch: `sudo pacman -S gcc make ncurses` (`script` is in `util-linux`)

## Build

```bash
make            # builds every program into build/
```

## Run

```bash
# Game: reads the board size and the snake length, then needs a real terminal.
# Left/right arrows move the tank, space shoots.
build/game                # then type: 15 4 <Enter>
```

The 15-puzzle prints the solved board, then a shuffle, then reads moves
(real output; the shuffle is random):

```console
$ build/puzzle < /dev/null
1 2 3 4 
5 6 7 8 
9 A B C 
D E F   

3 2 8 7 
F 4 B A 
9 D 1 E 
6   5 C 

```

## Tests

```bash
make test
```

- `tests/unit_tests.cc` (AddressSanitizer + UBSan):
  - **15-puzzle** — `build_mat` gives the solved board and `win_lose`
    recognises it; each of `w`/`s`/`a`/`d` moves the right tile into the gap,
    a move off the board changes nothing, undoing a sequence of moves is a win
    again, and `rand_mat` keeps the same 16 tiles;
  - **extended Euclid** — `eu_ex(a, b)` returns a Bézout pair
    (`a·x + b·y = gcd`) for 1 < a < 300; `inv(n, 256)` is the inverse of every
    odd `n`; encrypting a byte with `n` and then with `inv(n)` returns it;
  - **game geometry** — `conv` maps positions 0 … z²−1 onto every cell of a
    z×z board exactly once, each step to a neighbouring cell (the snake's
    zig-zag path), and shooting a snake splits it at the hit position.
- `tests/smoke_game.sh` runs the game headless in a pseudo-terminal (`script`)
  with no key presses and checks that it ends by itself with `Game Over`, and
  that the puzzle starts from the solved board.

## Project layout

```
GameNcurses/              game: snake, bullet, tank and game classes (header-only) + main.cc
Puzzle/                   15-puzzle class
EuclidesExtendido/        extended Euclid / modular inverse
ListaDoblementeEnlazada/  doubly linked list stub
tests/                    unit tests and the headless smoke test
```

## Known limitations

- The 15-puzzle could never be won: `win_lose` asked for 15 matching cells
  out of 16, which a permutation cannot give. Fixed (all 16), with a test.
- `rand_mat` shuffles with random swaps, so half of the boards it produces are
  unsolvable.
- Moving with `a` prints two debug lines (`fil …`, `col …`).
- `euclides` is unfinished (see above) and `lista-doble` is an empty stub.

## Background

Written for an objects and data abstraction course at university, 2016–2018.

## License

MIT — see [LICENSE](../LICENSE).
