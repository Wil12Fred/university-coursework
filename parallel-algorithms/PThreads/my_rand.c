/* my_rand.c -- linear congruential generator, see my_rand.h. */
#include "my_rand.h"

#define MR_MULTIPLIER 279470273ULL
#define MR_MODULUS    4294967291ULL

unsigned my_rand(unsigned* seed_p) {
   unsigned long long z = ((unsigned long long) *seed_p * MR_MULTIPLIER) % MR_MODULUS;
   *seed_p = (unsigned) z;
   return (unsigned) z;
}

double my_drand(unsigned* seed_p) {
   return my_rand(seed_p) / (double) MR_MODULUS;
}
