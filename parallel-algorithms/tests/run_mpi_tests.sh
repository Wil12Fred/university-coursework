#!/usr/bin/env bash
# MPI tests; needs mpicc/mpirun (Open MPI). Run after `make mpi build/oddeven_test`.
set -u
cd "$(dirname "$0")/.."
MPIRUN=${MPIRUN:-mpirun --oversubscribe}
fail=0
for np in 1 2 4; do
  $MPIRUN -np $np build/oddeven_test || { echo "FAIL oddeven_test -np $np"; fail=1; }
done
expected=$(python3 tests/matvec_case.py --expected)
for np in 1 2 4; do
  actual=$(python3 tests/matvec_case.py | $MPIRUN -np $np build/mulmatrizvector | tail -1)
  if [ "$actual" == "$expected" ]; then echo "ok   mulmatrizvector y = A x on $np processes"
  else echo "FAIL mulmatrizvector -np $np"; echo " got: ${actual:0:120}"; echo "want: ${expected:0:120}"; fail=1; fi
done
$MPIRUN -np 4 build/oddevensort | grep -c 'Elapsed time' | grep -qx 4 && echo "ok   oddevensort prints one time per process" || { echo "FAIL oddevensort run"; fail=1; }
exit $fail
