# Iluminacion con OpenGL

OpenGL lighting exercise for the Computer Graphics course (Computación Gráfica, UCSP, 2018).
A turtle made of spheres is lit by three fixed-function OpenGL lights: one directional,
one positional and one spotlight. You can switch each light on or off, move it around the
scene and aim the spotlight with the mouse.

![Turtle lit by the directional light](docs/screenshot.png)

*The screenshot shows the directional light switched on (F8, F9), with its parallel,
meridian and direction vector drawn. All lights start off, so at launch the turtle is lit only by the dim ambient light.*

## Build

Needs a C++ compiler and freeglut (`sudo apt install freeglut3-dev` on Debian/Ubuntu,
`pacman -S freeglut` on Arch). On macOS the system GLUT framework is used.

```sh
make
```

## Run

```sh
./iluminacion
```

| Key | Action |
|---|---|
| F8 | select the next light (0 directional, 1 positional, 2 spot) |
| F9 | switch the selected light on or off |
| F10 | (spot selected) toggle between moving the spot and aiming it |
| mouse move / drag | move the selected light / drag moves it closer or farther |
| F1 | stop: leave light mode, freeze the camera |
| F2 | examine mode: the mouse orbits the camera, drag zooms |
| F3 | walk mode: drag to walk and turn |
| F6 | reset the camera |
| c | toggle back-face culling |
| i | command mode: type `fd 1`, `rt 30`, `home`, `exit`... then Enter |
| h | print help to the terminal |
| q / Esc | quit |

## Layout

| File | Contents |
|---|---|
| `main.cpp` | GLUT window, input handlers, scene setup |
| `Light.h` | `Light` class: directional / positional / spot, movement on a sphere |
| `Camara.h` | camera with examine and walk modes |
| `primitivas.h` | turtle model and the light helpers (parallel, meridian, spot cone) |
| `Vector_tools.h` | small vector math helpers |
