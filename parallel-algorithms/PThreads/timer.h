/* timer.h -- wall-clock timer used by the Pthreads exercises.
 *
 * The exercises come from P. Pacheco, "An Introduction to Parallel
 * Programming" (ch. 4), which ships this helper separately; it was never
 * committed here. This is a compatible re-implementation of its interface.
 */
#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

/* Stores the current time, in seconds, into the double `now`. */
#define GET_TIME(now) { \
   struct timeval t; \
   gettimeofday(&t, NULL); \
   now = t.tv_sec + t.tv_usec/1000000.0; \
}

#endif
