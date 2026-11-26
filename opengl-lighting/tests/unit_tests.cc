// Unit tests of the vector maths and the light movement, which need no window.
#include <cmath>
#include <cstdio>
#include "../Light.h"

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

static bool near(float a, float b, float eps = 1e-4f) { return std::fabs(a - b) < eps; }
static float len(const float *v) { return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); }

static void test_vectors() {
  int ierr = 0;
  float x = 3, y = 0, z = 4;
  VectorNormalize(&ierr, &x, &y, &z);
  CHECK(!ierr && near(x, 0.6f) && near(y, 0) && near(z, 0.8f), "normalize (3,0,4) -> (%g,%g,%g)", x, y, z);

  x = y = z = 0;
  VectorNormalize(&ierr, &x, &y, &z);
  CHECK(ierr && near(z, 1), "a zero vector must set ierr and give (0,0,1)");

  ierr = 0;
  float wx, wy, wz;  // x cross y = z
  UnitVectorVV(&ierr, &wx, &wy, &wz, 1, 0, 0, 0, 1, 0);
  CHECK(!ierr && near(wx, 0) && near(wy, 0) && near(wz, 1), "x cross y = (%g,%g,%g)", wx, wy, wz);
  UnitVectorVV(&ierr, &wx, &wy, &wz, 0, 1, 0, 0, 0, 1);  // y cross z = x
  CHECK(!ierr && near(wx, 1) && near(wy, 0) && near(wz, 0), "y cross z = (%g,%g,%g)", wx, wy, wz);
  UnitVectorVV(&ierr, &wx, &wy, &wz, 0, 0, 1, 1, 0, 0);  // z cross x = y
  CHECK(!ierr && near(wx, 0) && near(wy, 1) && near(wz, 0), "z cross x = (%g,%g,%g)", wx, wy, wz);
  UnitVectorPP(&ierr, &wx, &wy, &wz, 1, 1, 1, 1, 1, 3);
  CHECK(!ierr && near(wz, 1) && near(wx, 0), "unit vector from (1,1,1) to (1,1,3)");

  // a quarter turn about Y takes +Z to +X; four of them come back; the
  // length and the height never change
  float v[3] = {0, 0, 2};
  VectorRotY(v, PI_VALUE / 2);
  CHECK(near(v[0], 2, 1e-3f) && near(v[2], 0, 1e-3f), "rotY(+Z, 90deg) = (%g,%g,%g)", v[0], v[1], v[2]);
  float w[3] = {1, 0.5f, -2};
  float lw = len(w);
  for (int i = 0; i < 4; i++) VectorRotY(w, PI_VALUE / 2);
  CHECK(near(w[0], 1, 1e-3f) && near(w[1], 0.5f) && near(w[2], -2, 1e-3f), "4 quarter turns: (%g,%g,%g)", w[0], w[1], w[2]);
  CHECK(near(len(w), lw, 1e-3f), "rotY changed the length");

  // latitude: going up stops just short of the pole, keeping the length
  float u[3] = {0, 0, 3};
  for (int i = 0; i < 100; i++) VectorRotXZ(u, 0.1f, TRUE);
  CHECK(near(len(u), 3, 1e-3f), "rotXZ changed the length to %g", len(u));
  CHECK(u[1] > 2.99f && u[1] < 3.0f, "rotXZ should stop below the pole, y = %g", u[1]);
  CHECK(u[2] > 0, "rotXZ went over the pole (z = %g)", u[2]);
}

static void test_light() {
  Light l;
  CHECK(l.type == AGA_DIRECTIONAL && !l.switched, "default light");
  CHECK(near(len(l.spotDirection), 1), "default spot direction is not unit");

  float d0 = len(l.position);
  l.Rotar_Luces_Longitud(0.7f);
  CHECK(near(len(l.position), d0, 1e-3f) && near(l.position[1], 1), "longitude move left the sphere");

  // moving closer/farther goes along the radius by exactly `step`
  float dir[3] = {l.position[0] / d0, l.position[1] / d0, l.position[2] / d0};
  l.Acercar_Alejar_Luces(0.5f);
  CHECK(near(len(l.position), d0 + 0.5f, 1e-3f), "distance %g after +0.5, expected %g", len(l.position), d0 + 0.5f);
  CHECK(near(l.position[0] / len(l.position), dir[0], 1e-3f), "direction changed when moving away");
  for (int i = 0; i < 20; i++) l.Acercar_Alejar_Luces(-0.5f);
  CHECK(len(l.position) >= 0.8f, "light got closer than 0.8 (%g)", len(l.position));
}

int main() {
  test_vectors();
  test_light();
  if (failures) {
    std::fprintf(stderr, "%d check(s) failed\n", failures);
    return 1;
  }
  std::printf("unit tests: all checks passed\n");
  return 0;
}
