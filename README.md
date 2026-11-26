# university-coursework

Assignments from a computer-science degree (2016–2019), one folder per course
project. Each folder is self-contained, with its own `README.md`, build
instructions and (where it builds headless) a CI workflow under
`.github/workflows/<folder>.yml` that runs only when that folder changes.

| Folder | Course topic | Stack |
|---|---|---|
| [`algorithms-and-data-structures`](algorithms-and-data-structures) | Sorting benchmarks, AVL / red-black / BST trees, an ncurses bomb game | C++ |
| [`parallel-algorithms`](parallel-algorithms) | Cache-blocked matrix multiply, Pthreads exercises, two MPI programs | C, Pthreads, MPI |
| [`intro-oop-cpp`](intro-oop-cpp) | Linked list, bee-walk DP, matrix Fibonacci with big numbers | C++ |
| [`objects-and-data-abstraction`](objects-and-data-abstraction) | ncurses tank-vs-snake game, 15-puzzle | C++ |
| [`computer-architecture-mips`](computer-architecture-mips) | Ten short MIPS assembly exercises (SPIM/MARS) | MIPS |
| [`mini0-lexer-parser`](mini0-lexer-parser) | Lexer and top-down parser for a toy language | Python |
| [`automata-playground`](automata-playground) | Finite automata, derivations, Moore machine and regex in the browser | HTML, JS, vis.js |
| [`opengl-lighting`](opengl-lighting) | Directional, point and spot lights on a GLUT scene | C++, OpenGL |
| [`android-face-tracker`](android-face-tracker) | Face tracking with Google Mobile Vision, saves each new face | Android, Java |
| [`android-sensor-list`](android-sensor-list) | Lists the device's sensors with the Navigation component | Android, Kotlin |
| [`jsp-login-example`](jsp-login-example) | JSP + Servlet + DAO login against MySQL (teaching sample, not secure) | Java EE |

Each folder keeps the full history of the repository it came from:
`git log -- <folder>` shows it.
