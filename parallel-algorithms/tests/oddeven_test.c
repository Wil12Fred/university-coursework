/* Test of the MPI odd-even transposition sort. Includes ../oddevensort.c with
 * its main() renamed, runs init() + parallel_sort() on every rank, and checks
 *  - no value was lost or duplicated (global histogram before == after), and
 *  - the data is globally partitioned: every value on rank r is <= every
 *    value on rank r+1.
 * Run with: mpirun -np <P> build/oddeven_test */
#define main oddevensort_main
#include "../oddevensort.c"
#undef main

int main(int argc, char *argv[]) {
  int rank, size, i, fail = 0;
  int data[N], before[100] = {0}, after[100] = {0}, gb[100], ga[100];
  int lo, hi, *los = NULL, *his = NULL;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  init(data, rank);
  for (i = 0; i < N; i++) before[data[i]]++;
  parallel_sort(data, rank, size);
  for (i = 0; i < N; i++) after[data[i]]++;

  /* the last phase exchanges without re-sorting, so order locally first */
  qsort(data, N, sizeof(int), &cmp);
  lo = data[0];
  hi = data[N - 1];

  MPI_Reduce(before, gb, 100, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(after, ga, 100, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    los = malloc(size * sizeof(int));
    his = malloc(size * sizeof(int));
  }
  MPI_Gather(&lo, 1, MPI_INT, los, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Gather(&hi, 1, MPI_INT, his, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    for (i = 0; i < 100; i++)
      if (gb[i] != ga[i]) {
        fprintf(stderr, "FAIL value %d: %d copies before, %d after\n", i, gb[i], ga[i]);
        fail = 1;
      }
    for (i = 0; i + 1 < size; i++)
      if (his[i] > los[i + 1]) {
        fprintf(stderr, "FAIL rank %d holds %d but rank %d holds %d\n", i, his[i], i + 1, los[i + 1]);
        fail = 1;
      }
    if (!fail) printf("ok   oddevensort on %d processes\n", size);
    free(los);
    free(his);
  }
  MPI_Bcast(&fail, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Finalize();
  return fail;
}
