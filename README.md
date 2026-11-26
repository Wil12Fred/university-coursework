# university-coursework

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Assignments from a computer-science degree (2016–2019), one folder per course
project, from MIPS assembly and MPI to Android apps and a JSP login. Each
folder is self-contained, with its own README, build, tests, and a CI
workflow (`.github/workflows/<folder>.yml`) that runs only when that folder
changes.

| Folder | Course topic | Stack | CI |
|---|---|---|---|
| [`algorithms-and-data-structures`](algorithms-and-data-structures) | Sorting benchmarks, AVL / red-black / BST trees, an ncurses bomb game | C++ | [![algorithms-and-data-structures](https://github.com/Wil12Fred/university-coursework/actions/workflows/algorithms-and-data-structures.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/algorithms-and-data-structures.yml) |
| [`parallel-algorithms`](parallel-algorithms) | Cache-blocked matrix multiply, Pthreads linked lists and pi, two MPI programs | C, Pthreads, MPI | [![parallel-algorithms](https://github.com/Wil12Fred/university-coursework/actions/workflows/parallel-algorithms.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/parallel-algorithms.yml) |
| [`intro-oop-cpp`](intro-oop-cpp) | Linked list, bee-walk DP, matrix Fibonacci with big numbers | C++ | [![intro-oop-cpp](https://github.com/Wil12Fred/university-coursework/actions/workflows/intro-oop-cpp.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/intro-oop-cpp.yml) |
| [`objects-and-data-abstraction`](objects-and-data-abstraction) | ncurses tank-vs-snake game, 15-puzzle, extended Euclid | C++ | [![objects-and-data-abstraction](https://github.com/Wil12Fred/university-coursework/actions/workflows/objects-and-data-abstraction.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/objects-and-data-abstraction.yml) |
| [`computer-architecture-mips`](computer-architecture-mips) | Ten short MIPS assembly exercises, run under SPIM | MIPS | [![computer-architecture-mips](https://github.com/Wil12Fred/university-coursework/actions/workflows/computer-architecture-mips.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/computer-architecture-mips.yml) |
| [`mini0-lexer-parser`](mini0-lexer-parser) | Lexer and top-down parser for a toy language | Python | [![mini0-lexer-parser](https://github.com/Wil12Fred/university-coursework/actions/workflows/mini0-lexer-parser.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/mini0-lexer-parser.yml) |
| [`automata-playground`](automata-playground) | Finite automata, derivations, Moore machine and regex in the browser | HTML, JS, vis.js | [![automata-playground](https://github.com/Wil12Fred/university-coursework/actions/workflows/automata-playground.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/automata-playground.yml) |
| [`opengl-lighting`](opengl-lighting) | Directional, point and spot lights on a GLUT scene | C++, OpenGL | [![opengl-lighting](https://github.com/Wil12Fred/university-coursework/actions/workflows/opengl-lighting.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/opengl-lighting.yml) |
| [`android-face-tracker`](android-face-tracker) | Face tracking with Google Mobile Vision, saves each new face | Android, Java | [![android-face-tracker](https://github.com/Wil12Fred/university-coursework/actions/workflows/android-face-tracker.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/android-face-tracker.yml) |
| [`android-sensor-list`](android-sensor-list) | Lists the device's sensors with the Navigation component | Android, Kotlin | [![android-sensor-list](https://github.com/Wil12Fred/university-coursework/actions/workflows/android-sensor-list.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/android-sensor-list.yml) |
| [`jsp-login-example`](jsp-login-example) | JSP + Servlet + DAO login against MySQL (teaching sample) | Java EE | [![jsp-login-example](https://github.com/Wil12Fred/university-coursework/actions/workflows/jsp-login-example.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/jsp-login-example.yml) |

## Features

- Every folder builds and runs its tests in GitHub Actions: unit tests of the
  data structures, numerics and logic (C/C++ ones under AddressSanitizer),
  golden-output tests of the command-line programs, MPI programs under
  `mpirun`, MIPS programs under SPIM, a headless-browser test of the automata
  page, and headless runs of the GUI programs.
- Bugs found while adding the tests are fixed and listed under *Known
  limitations* in each folder's README.

## Requirements

Per folder — see each README (C/C++ toolchain, Open MPI, SPIM, Python + uv,
Node.js, JDK 8/17, Android SDK).

## Build

```bash
cd <folder>
# then the command in that folder's README, e.g. `make`, `./gradlew assembleDebug`, `./mvnw package`
```

## Run

See each folder's README; every one shows a real run.

## Tests

Each folder's README has a *Tests* section; the usual entry point is
`make test` (C, C++, MIPS), `uv run pytest` (Python), `npm test` (web),
`./gradlew testDebugUnitTest` (Android) or `./mvnw test` (Java EE).

## Project layout

```
<folder>/                     one course project, self-contained
.github/workflows/<folder>.yml  its CI, filtered on <folder>/**
LICENSE                       MIT, for every folder
```

## Known limitations

Listed per folder. Common to all: this is coursework, kept close to what was
handed in; deprecated toolchains (JDK 8 Android builds, GLUT, `javax.servlet`)
are kept rather than ported.

## Background

Each folder keeps the full history of the repository it came from:
`git log -- <folder>` shows it. The projects were written for university
courses between 2016 and 2019.

## License

MIT — see [LICENSE](LICENSE). Vendored third-party code keeps its own
license (ttmath in `intro-oop-cpp/third_party/`, vis.js in
`automata-playground/`).
