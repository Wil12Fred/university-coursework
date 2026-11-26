/* my_rand.h -- thread-safe pseudo-random numbers for the linked-list exercises.
 *
 * Compatible re-implementation of the helper that accompanies P. Pacheco,
 * "An Introduction to Parallel Programming"; the original was not committed.
 * Each thread keeps its own seed, so no shared state is touched.
 */
#ifndef MY_RAND_H
#define MY_RAND_H

unsigned my_rand(unsigned* seed_p);   /* next value in [0, 2^32 - 5) */
double   my_drand(unsigned* seed_p);  /* next value in [0, 1)        */

#endif
