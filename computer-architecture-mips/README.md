# computer-architecture-mips

[![CI](https://github.com/Wil12Fred/university-coursework/actions/workflows/computer-architecture-mips.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/computer-architecture-mips.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

Short MIPS32 assembly exercises from a computer architecture course, written
for the SPIM / MARS simulators: loops over arrays and strings, console I/O
through SPIM's `syscall` services, and a palindrome check. Every program runs
under SPIM in CI and is compared with a golden output.

## Features

| File | What it does |
|---|---|
| `hello.asm` | Prints `ABCDEFG` |
| `pedir.asm` | Reads a string and echoes it back |
| `length.asm` | Reads a word, prints it one character per line, then its length |
| `letra.asm` | Meant to print the first letter of a word; returns right after reading it (unfinished) |
| `aux.asm` | Minimum and maximum of a word array (`min = 8`, `max = 13` for the data in the file) |
| `Practica/sum.asm` | Sum of the array `1..5` |
| `Practica/pascal.asm` | Prints the Fibonacci numbers 2, 3, 5, 8 (loop up to 5) |
| `Practica/swap.asm` | Reads an index `x` and swaps `A[x]` and `A[x+1]` in memory (prints nothing) |
| `Practica/eco.asm` | Reads a string and an integer and prints both |
| `Practica/pal.asm` | Reads a word and says whether it is a palindrome |

They use SPIM's `syscall` services 1 (print int), 4 (print string), 5 (read
int), 8 (read string), 10 (exit) and 11 (print char). They are MIPS, not x86,
and do not assemble with nasm.

## Requirements

- Debian/Ubuntu: `sudo apt install spim`
- Arch: `spim` from the AUR (or the MARS simulator, Java)

## Build

Nothing to build: SPIM assembles each file when it loads it.

## Run

```bash
spim -file hello.asm
echo "reconocer" | spim -file Practica/pal.asm
```

SPIM prints a banner and `Loaded: …/exceptions.s` first, then the program's
output, e.g. `Ingrese una palabra: La palabra que ingreso es palindromo`.
Or open a file in MARS and press *Assemble*, then *Run*.

## Tests

```bash
make test
```

`tests/run_golden.sh` runs every program under `spim -quiet -file` with
`tests/golden/<program>.<case>.in` on stdin, drops SPIM's banner, and
compares the output byte for byte with `<program>.<case>.out`. The expected
outputs were written from what each program is supposed to do (min/max 8 and
13, the sum 15, Fibonacci 2 3 5 8, …), not captured from a run. `pal.asm` has
six cases: odd and even palindromes, a single letter, a plain non-palindrome,
and two words that only differ in their outer letters (`abcdedcxy`, `xbby`).

## Project layout

```
*.asm, Practica/*.asm   the exercises
tests/                  golden inputs/outputs and the SPIM runner
Makefile                `make test`
```

## Known limitations

- `pal.asm` compared only the middle of the word (its two pointers walked the
  wrong way) and called a word a palindrome when only its last compared pair
  differed; it also hung SPIM because of a non-ASCII character in a comment.
  All fixed; the outer-mismatch tests cover them.
- `letra.asm` is unfinished: it returns with `jr $ra` right after reading the
  word, and the code after it would print a byte with the print-string call.
- `swap.asm` does not check that `x` and `x+1` are inside the array.
- Strings read with syscall 8 keep their newline; `length.asm` prints it and
  does not count it.

## Background

Written for a computer architecture course at university, 2016.

## License

MIT — see [LICENSE](../LICENSE).
