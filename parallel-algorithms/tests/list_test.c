/* Tests of the three shared sorted linked lists (one mutex, one mutex per
 * node, read-write lock). The program's source is included with main()
 * renamed; build once per variant:
 *   -DONE_MUT   PThreads/pth_ll_one_mut.c   (caller takes `mutex`)
 *   -DRWL       PThreads/pth_ll_rwl.c       (caller takes `rwlock`)
 *   -DMULT_MUT  PThreads/pth_ll_mult_mut.c  (the list locks its own nodes)
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define main list_program_main
#if defined(ONE_MUT)
#include "../PThreads/pth_ll_one_mut.c"
#define WRITE_LOCK() pthread_mutex_lock(&mutex)
#define READ_LOCK() pthread_mutex_lock(&mutex)
#define UNLOCK() pthread_mutex_unlock(&mutex)
#define VARIANT "one mutex"
#elif defined(RWL)
#include "../PThreads/pth_ll_rwl.c"
#define WRITE_LOCK() pthread_rwlock_wrlock(&rwlock)
#define READ_LOCK() pthread_rwlock_rdlock(&rwlock)
#define UNLOCK() pthread_rwlock_unlock(&rwlock)
#define VARIANT "read-write lock"
#elif defined(MULT_MUT)
#include "../PThreads/pth_ll_mult_mut.c"
#define WRITE_LOCK() ((void)0)
#define READ_LOCK() ((void)0)
#define UNLOCK() ((void)0)
#define VARIANT "mutex per node"
#else
#error "define ONE_MUT, RWL or MULT_MUT"
#endif
#undef main

static int failures = 0;
#define CHECK(cond, msg)                                                 \
  do {                                                                   \
    if (!(cond)) {                                                       \
      ++failures;                                                        \
      fprintf(stderr, "FAIL [%s] %s:%d: %s\n", VARIANT, __FILE__, __LINE__, msg); \
    }                                                                    \
  } while (0)

/* 1 if the list is strictly increasing, and its length in *n */
static int strictly_sorted(int *n) {
  struct list_node_s *p = head;
  *n = 0;
  for (; p != NULL; p = p->next) {
    ++*n;
    if (p->next != NULL && p->next->data <= p->data) return 0;
  }
  return 1;
}

static void sequential(void) {
  int n;
  CHECK(Is_empty(), "a new list is empty");
  CHECK(Insert(5) == 1 && Insert(1) == 1 && Insert(9) == 1 && Insert(3) == 1, "inserting new keys returns 1");
  CHECK(Insert(5) == 0, "inserting a duplicate returns 0");
  CHECK(strictly_sorted(&n) && n == 4, "list holds 1 3 5 9 in order");
  CHECK(Member(3) && Member(9) && !Member(4) && !Member(10), "Member finds exactly the inserted keys");
  CHECK(Delete(1) == 1 && Delete(9) == 1, "deleting head and tail returns 1");
  CHECK(Delete(4) == 0, "deleting a missing key returns 0");
  CHECK(strictly_sorted(&n) && n == 2 && Member(3) && Member(5) && !Member(1), "list holds 3 5");
  CHECK(Delete(3) == 1 && Delete(5) == 1 && Is_empty(), "list is empty again");
}

/* Thread r owns the keys k with k % THREADS == r, so the final contents are
 * known; the threads still interleave in the same list, so a lost update or
 * a broken link shows up as a missing or extra key. */
#define THREADS 4
#define KEYS 2000
static void *worker(void *arg) {
  long r = (long)arg;
  int k;
  for (k = (int)r; k < KEYS; k += THREADS) { WRITE_LOCK(); Insert(k); UNLOCK(); }
  for (k = (int)r; k < KEYS; k += THREADS)
    if (k % 3 == 0) { WRITE_LOCK(); Delete(k); UNLOCK(); }
  for (k = (int)r; k < KEYS; k += THREADS) { READ_LOCK(); Member(k); UNLOCK(); }
  return NULL;
}

static void concurrent(void) {
  pthread_t t[THREADS];
  long r;
  int k, n, ok = 1;
  for (r = 0; r < THREADS; r++) pthread_create(&t[r], NULL, worker, (void *)r);
  for (r = 0; r < THREADS; r++) pthread_join(t[r], NULL);
  CHECK(strictly_sorted(&n), "list is sorted after concurrent use");
  for (k = 0; k < KEYS; k++)
    if (Member(k) != (k % 3 != 0)) ok = 0;
  CHECK(ok, "exactly the keys not divisible by 3 remain");
  CHECK(n == KEYS - (KEYS + 2) / 3, "list length after concurrent use");
}

int main(void) {
#if defined(ONE_MUT)
  pthread_mutex_init(&mutex, NULL);
#elif defined(RWL)
  pthread_rwlock_init(&rwlock, NULL);
#else
  pthread_mutex_init(&head_mutex, NULL);
#endif
  sequential();
  concurrent();
  Free_list();
  if (failures) {
    fprintf(stderr, "%d check(s) failed\n", failures);
    return 1;
  }
  printf("ok   linked list (%s)\n", VARIANT);
  return 0;
}
