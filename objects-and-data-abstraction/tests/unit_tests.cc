// Unit tests for the parts of these programs that do not need a terminal:
// the 15-puzzle rules, extended Euclid / modular inverse / byte cipher, and the
// board geometry and snake splitting of the ncurses game.
#include <cstdio>
#include <cstring>
#include <set>
#include <ncurses.h>

static int failures = 0;
#define CHECK(cond, ...)                                                    \
  do {                                                                      \
    if (!(cond)) {                                                          \
      ++failures;                                                           \
      std::fprintf(stderr, "FAIL %s:%d: %s -- ", __FILE__, __LINE__, #cond); \
      std::fprintf(stderr, __VA_ARGS__);                                    \
      std::fprintf(stderr, "\n");                                           \
    }                                                                       \
  } while (0)

#include "../Puzzle/Puzzle.h"

#define main euclides_main
#include "../EuclidesExtendido/ext.cc"
#undef main

#include "../GameNcurses/funciones.h"
#include "../GameNcurses/serpiente.h"

static const char SOLVED[4][4] = {{'1', '2', '3', '4'},
                                  {'5', '6', '7', '8'},
                                  {'9', 'A', 'B', 'C'},
                                  {'D', 'E', 'F', ' '}};

static void test_puzzle() {
  char m[4][4] = {};
  Puzzle p(m);
  p.build_mat();
  CHECK(std::memcmp(p.matriz, SOLVED, sizeof SOLVED) == 0, "build_mat is not the solved board");
  CHECK(p.win_lose(), "the solved board is not recognised as a win");

  int f, c;
  p.locate_space(f, c);
  CHECK(f == 3 && c == 3, "space should start at (3,3), got (%d,%d)", f, c);

  char op = 'w';  // the tile below the space moves up: none here, so no change
  p.move_space(op, f, c);
  CHECK(std::memcmp(p.matriz, SOLVED, sizeof SOLVED) == 0, "a move off the board changed it");

  op = 's';  // tile above the space ('C') moves down
  p.move_space(op, f, c);
  p.locate_space(f, c);
  CHECK(f == 2 && c == 3 && p.matriz[3][3] == 'C', "'s' did not move the space up");
  CHECK(!p.win_lose(), "a scrambled board counts as a win");

  op = 'd';  // tile left of the space ('B') moves right
  p.move_space(op, f, c);
  p.locate_space(f, c);
  CHECK(f == 2 && c == 2 && p.matriz[2][3] == 'B', "'d' did not move the space left");

  op = 'a'; p.move_space(op, f, c);
  op = 'w'; p.move_space(op, f, c);
  CHECK(p.win_lose(), "undoing the moves does not give back a win");

  // shuffling keeps the same 16 symbols
  p.rand_mat();
  std::multiset<char> before(&SOLVED[0][0], &SOLVED[0][0] + 16), after(&p.matriz[0][0], &p.matriz[0][0] + 16);
  CHECK(before == after, "rand_mat lost or duplicated a tile");
}

static void test_euclides() {
  // Bezout: a*x + b*y == gcd(a, b)
  for (int a = 1; a < 300; a++)
    for (int b = 1; b < 300; b += 7) {
      pii r = eu_ex(a, b);
      int g = a, h = b;
      while (h) { int t = g % h; g = h; h = t; }
      CHECK(a * r.first + b * r.second == g, "eu_ex(%d,%d) is not a Bezout pair", a, b);
    }
  for (int n = 1; n < 256; n += 2) {
    int i = inv(n, 256);
    CHECK(i >= 0 && i < 256 && (n * i) % 256 == 1, "inv(%d,256) = %d", n, i);
    for (int c = 0; c < 256; c++) {
      char e = enc(char(c), n);
      CHECK((unsigned char)enc(e, i) == c, "enc with %d then its inverse does not round-trip %d", n, c);
    }
  }
}

static void test_game_geometry() {
  // conv walks the z*z board in a zig-zag: every cell exactly once, and each
  // step moves to a neighbouring cell
  for (int z = 2; z <= 12; z++) {
    std::set<pii> cells;
    for (int p = 0; p < z * z; p++) {
      pii a = conv(p, z);
      CHECK(a.first >= 0 && a.first < z && a.second >= 0 && a.second < z, "conv(%d,%d) off board", p, z);
      cells.insert(a);
      if (p) {
        pii b = conv(p - 1, z);
        CHECK(std::abs(a.first - b.first) + std::abs(a.second - b.second) == 1,
              "conv(%d,%d) is not next to conv(%d,%d)", p, z, p - 1, z);
      }
    }
    CHECK((int)cells.size() == z * z, "conv does not cover the %dx%d board", z, z);
  }

  // a snake on positions 10..15; shooting position 12 keeps 13..15 in it
  serpiente s(10, 6, nullptr);
  CHECK(s.colision(0, 10) && s.colision(0, 15) && !s.colision(0, 16) && !s.colision(0, 9), "collision range");
  s.act_tam(12);
  CHECK(s.Get() == pii(13, 3), "split left (%d,%d), expected (13,3)", s.Get().first, s.Get().second);
}

int main() {
  test_puzzle();
  test_euclides();
  test_game_geometry();
  if (failures) {
    std::fprintf(stderr, "%d check(s) failed\n", failures);
    return 1;
  }
  std::printf("unit tests: all checks passed\n");
  return 0;
}
