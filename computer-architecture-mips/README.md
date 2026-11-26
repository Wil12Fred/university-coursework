# Arquitectura de Computadores — MIPS assembly

Short **MIPS32** assembly exercises from the *Computer Architecture* course
(UCSP, 2016), written for the SPIM / MARS simulators (they use SPIM's
`syscall` services: 1 print int, 4 print string, 5 read int, 8 read string,
10 exit, 11 print char). They are not x86 and do not assemble with nasm.

| File | What it does |
|---|---|
| `hello.asm` | Prints `ABCDEFG` |
| `pedir.asm` | Reads a string and echoes it back |
| `length.asm` | Reads a word, prints it one character per line, then its length |
| `letra.asm` | Meant to print the first letter of a word (exits early at `jr $ra`; unfinished) |
| `aux.asm` | Minimum and maximum of a word array (`min = 8`, `max = 13` for the data in the file) |
| `Practica/sum.asm` | Sum of the array `1..5` |
| `Practica/pascal.asm` | Prints the Fibonacci numbers 2, 3, 5, 8 (loop up to 5) |
| `Practica/swap.asm` | Reads an index `x` and swaps `A[x]` and `A[x+1]` in memory (prints nothing) |
| `Practica/eco.asm` | Reads a string and an integer and prints both |
| `Practica/pal.asm` | Reads a word and says whether it is a palindrome |

## Run

With [SPIM](https://spimsimulator.sourceforge.net/) (`apt install spim` on Debian/Ubuntu):

```bash
spim -file hello.asm
echo "reconocer" | spim -file Practica/pal.asm
```

Or open the file in the MARS simulator (Java) and press *Assemble*, then *Run*.

**Not verified:** no MIPS simulator was available when this README was
written, so none of these programs have been run here; the descriptions above
come from reading the code.
