# Teoría de la Computación — "The Graph Machine"

A static web page for a Theory of Computation course (UCSP). You describe a
finite automaton as a transition table and the page:

- derives an input string step by step and says whether it is accepted
  (`Verdadero` / `Falso`);
- draws the automaton as a graph (vis.js);
- builds a Moore machine graph from a table with outputs;
- produces a regular expression for the accepted language (button
  `ExpresionRegular`, state elimination).

UI text is in Spanish.

## Run

No build step. Open the page in a browser:

```bash
xdg-open "Pagina Automatas/Pagina.html"     # or just double-click it
```

Example: *Numero de entradas* = 2, *Numero de estados* = 2, **Crear tabla**,
fill `A→(A,B)`, `B→(B,A)`, acceptance state `A`, string `11`, then
**Derivar cadena**:

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

## Layout

```
Pagina Automatas/
  Pagina.html        main page (all logic is inline JavaScript)
  Automata.html      earlier standalone prototype of the derivation step
  Expresiones.html   earlier prototype with a hard-coded 3-state automaton
  estilos.css, imagenes/   styling and images
  *.psd              Photoshop sources for the banners/background
  vis/dist/          vendored vis.js 4.10.0 (MIT/Apache-2.0, see vis/LICENSE-*)
```

`vis/dist` is required by the page and is kept vendored so it works offline.
