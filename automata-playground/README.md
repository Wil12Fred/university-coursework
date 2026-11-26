# automata-playground

[![CI](https://github.com/Wil12Fred/university-coursework/actions/workflows/automata-playground.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/automata-playground.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

"The Graph Machine": a static web page for a theory of computation course.
You describe a finite automaton as a transition table and the page derives
strings through it, draws it as a graph with vis.js, and turns it into a
regular expression by state elimination — all in inline JavaScript, no build.

## Features

- Derives an input string step by step and says whether it is accepted
  (`Verdadero` / `Falso`).
- Draws the automaton as a graph (vis.js), one node per state and one edge per
  transition.
- Builds a Moore machine graph from a table with outputs.
- Produces a regular expression for the accepted language (button
  `ExpresionRegular`).

UI text is in Spanish. States are named by letters: q0 = `A` (the initial
state), q1 = `B`, …

## Requirements

- Any modern browser to use the page.
- For the tests: Node.js 18+ and npm (Debian/Ubuntu: `sudo apt install nodejs
  npm`; Arch: `sudo pacman -S nodejs npm`). Playwright downloads its own
  headless Chromium.

## Build

No build step: the page and the vendored vis.js are plain files.

## Run

```bash
xdg-open "Pagina Automatas/Pagina.html"     # or just double-click it
```

Example: *Numero de entradas* = 2, *Numero de estados* = 2, **Crear tabla**,
fill `A→(A,B)`, `B→(B,A)`, acceptance state `A`, string `11`, then
**Derivar cadena**. The page shows (this is also what the tests read back):

```
A
1B
11A
11
Verdadero.
```

**Generar Automata de Estados Finitos** then draws 2 nodes / 4 edges, and
**ExpresionRegular** prints
`[(0|[(0)*,0]|[(1)*,0])] | [(1|[(0)*,1]|[(1)*,1]),(1|[(0)*,1]|[(1)*,1])]`.

## Tests

```bash
npm ci
npx playwright install chromium   # once; add --with-deps on a fresh Debian/Ubuntu
npm test
```

`tests/automaton.spec.js` opens the page from disk in headless Chromium and
uses it like a person would:

- the derivation of `11` through the parity automaton above is exactly
  `A, 1B, 11A, 11, Verdadero.`;
- `1` and `0111` are rejected, `0101` accepted;
- a 2-input, 3-state automaton draws 3 nodes and 6 edges, with the right
  edges into `B`;
- the regular expression of the example is the one shown above.

## Project layout

```
Pagina Automatas/
  Pagina.html        main page (all logic is inline JavaScript)
  Automata.html      earlier standalone prototype of the derivation step
  Expresiones.html   earlier prototype with a hard-coded 3-state automaton
  estilos.css, imagenes/   styling and images
  *.psd              Photoshop sources for the banners/background
  vis/dist/          vendored vis.js 4.10.0 (MIT/Apache-2.0, see vis/LICENSE-*)
tests/               Playwright tests
package.json         dev dependency on @playwright/test; `npm test`
```

`vis/dist` is required by the page and is kept vendored so it works offline.

## Known limitations

- The graph had one node per *input* instead of per *state*, so any
  automaton with a different number of inputs and states was drawn with
  missing nodes. Fixed, with a test.
- Only one accepting state is supported in the derivation (the field is
  compared as a single letter), and states are limited to 26 letters.
- Invalid table entries are not validated; a typo leads to `undefined` in the
  derivation.
- The regular expression is not simplified.

## Background

Written for a theory of computation course at university.

## License

MIT — see [LICENSE](../LICENSE). The vendored vis.js keeps its own
MIT/Apache-2.0 licenses.
