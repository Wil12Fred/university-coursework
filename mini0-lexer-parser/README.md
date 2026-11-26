# mini0-lexer-parser

[![CI](https://github.com/Wil12Fred/university-coursework/actions/workflows/mini0-lexer-parser.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/mini0-lexer-parser.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

A small lexer and a naive table-driven top-down parser, in plain Python, for
a toy imperative language in the style of "Mini-0" (keywords `fun`,
`if`/`else`, `while ... loop`, `end`, typed declarations such as `x : int`).
The grammar is a Python dictionary walked with an explicit stack.

## Features

- **Lexing** — a list of regular expressions (`token_exprs`) is tried in
  order at each position; whitespace and `//` / `/* */` comments are skipped,
  anything unmatched is reported on stderr as `[ERROR] Illegal character`.
- **Parsing** — the grammar lives in the `syntac` dictionary (one entry per
  non-terminal, each a list of alternative productions). `syn()` walks it with
  an explicit stack and prints either `Analisis sintactico correcto` or the
  first token it could not match, followed by the token → rule map it built.

## Requirements

- Python 3.9 or newer, no third-party packages to run it.
- [uv](https://docs.astral.sh/uv/) to run the tests (it installs pytest into
  a project-local `.venv`).
- Debian/Ubuntu: `sudo apt install python3`; Arch: `sudo pacman -S python uv`
  (on Debian/Ubuntu install uv with its official installer or `pipx install uv`).

## Build

Nothing to build.

## Run

Real output:

```console
$ python3 anLx.py examples/valid.txt
('x', 'IDENTIFIER')
(':', 'DOSPUNTOS')
('int', 'DATATYPE')
('\n', 'ENDLINE')
('y', 'IDENTIFIER')
(':', 'DOSPUNTOS')
('bool', 'DATATYPE')
('\n', 'ENDLINE')
('', 'ENDFILE')

 Analisis sintactico correcto
{0: 'IDENTIFIER', -1: 'decls', 1: 'DOSPUNTOS', 2: 'DATATYPE', 3: 'decls', 4: 'IDENTIFIER', 5: 'DOSPUNTOS', 6: 'DATATYPE', 7: 'ENDLINE', 8: 'ENDFILE'}
```

`examples/error.txt` (a function missing the `:` before its return type)
ends in:

```
 ERROR:
error en token:
('int', 'DATATYPE')
```

## Tests

```bash
uv run pytest
```

`tests/test_anlx.py`:

- **lexer** — the token stream of a declaration, of operators and literals
  (`<=`, `>=`, `!=`, chars, strings), skipping comments and runs of blank
  lines, and reporting an illegal character on stderr;
- **parser** — a set of valid programs (globals, array types, empty
  functions, a function with a local declaration) is accepted, and invalid
  ones are rejected naming the offending token;
- **golden** — `anLx.py` is run on every `tests/golden/*.txt` (four valid,
  four invalid programs) and its whole stdout must equal the committed `.out`;
- **documented limits** — the five limitations below are written as
  `xfail(strict=True)` tests, so they keep documenting the behaviour and turn
  into failures the day one of them is fixed.

## Project layout

```
anLx.py          lexer + grammar + parser, run as a script
examples/        the original sample programs
tests/           pytest tests and golden programs/outputs
pyproject.toml   uv project (pytest as a dev dependency); uv.lock pins it
```

## Known limitations

Properties of the original code, kept as-is and pinned by the xfail tests:

- The parser backtracks only partially: function bodies with statements
  (`examples/function.txt`, even a lone `return 1`) and functions with more
  than one parameter are rejected, although the grammar describes them.
- Keywords are matched as prefixes, so an identifier such as `doble` lexes as
  `do` + `ble`.
- `<` is tried before `<>`, so the `INEQUAL` token is never produced.
- A block comment on its own line leaves an empty line behind, which the
  grammar does not allow between declarations.
- On an error the offending token is the one after the furthest token matched,
  which is not always where the mistake is.

## Background

Written for a compilers course at university, 2019.

## License

MIT — see [LICENSE](../LICENSE).
