# AnalizadorLexico

A small lexer and naive top-down parser, written in Python, for a toy
imperative language in the style of "Mini-0" (keywords `fun`, `if`/`else`,
`while ... loop`, `end`, typed declarations such as `x : int`). University
compilers coursework (UCSP).

`anLx.py` does two things:

1. **Lexing** — a list of regular expressions (`token_exprs`) is tried in order
   at each position; whitespace and comments are skipped, anything unmatched is
   reported as `[ERROR] Illegal character`.
2. **Parsing** — the grammar lives in the `syntac` dictionary (one entry per
   non-terminal, each a list of alternative productions). `syn()` walks it with
   an explicit stack and prints either `Analisis sintactico correcto` or the
   first token it could not match.

## Requirements

Python 3 (no third-party packages). Tested with Python 3.14.

## Run

```bash
python3 anLx.py examples/valid.txt
```

Output (abridged): the token list, then the parse result.

```
('x', 'IDENTIFIER')
(':', 'DOSPUNTOS')
('int', 'DATATYPE')
...
 Analisis sintactico correcto
{0: 'IDENTIFIER', -1: 'decls', 1: 'DOSPUNTOS', ...}
```

`examples/error.txt` (a function missing the `:` before its return type)
ends in `ERROR: error en token: ('int', 'DATATYPE')`.

## Known limitations

These are properties of the original code, kept as-is:

- The parser backtracks only partially. Function bodies with statements
  (`examples/function.txt`) and functions with more than one parameter are
  rejected even though the grammar describes them.
- Keywords are matched as prefixes, so an identifier such as `doble` lexes as
  `do` + `ble`.

## Layout

```
anLx.py      lexer + grammar + parser, run as a script
examples/    sample input programs
```
