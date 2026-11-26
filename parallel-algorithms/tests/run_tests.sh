#!/usr/bin/env bash
# Invariant tests of the Pthreads programs. Their timings vary, so only the
# results are checked: the pi estimates, and that every list operation that
# was requested was counted exactly once.
set -u
cd "$(dirname "$0")/.."
fail=0
ok()   { echo "ok   $1"; }
bad()  { echo "FAIL $1"; fail=1; }

# pi: both estimates within 1e-6 of pi, and the threaded sum equal to the serial one
for prog in pth_pi_mutex pth_pi_busy2; do
  out=$(build/$prog 3 9999999)   # 3 threads: the slices start on odd and even terms || { bad "$prog exited non-zero"; continue; }
  if awk -F'= *' '
      /[Ee]st/ && !/Math/ { v[++n] = $2 }
      END {
        pi = atan2(0, -1); d = v[1] - v[2]
        if (n != 2) exit 1
        for (i = 1; i <= 2; i++) if (v[i] - pi > 1e-6 || pi - v[i] > 1e-6) exit 1
        if (d > 1e-9 || -d > 1e-9) exit 1
      }' <<<"$out"; then ok "$prog estimates pi"; else bad "$prog estimate"; echo "$out"; fi
done

# linked lists: inserted keys reported, and member + insert + delete == total ops
for prog in pth_ll_one_mut pth_ll_mult_mut pth_ll_rwl; do
  out=$(printf '1000\n100000\n0.8\n0.1\n' | build/$prog 4) || { bad "$prog exited non-zero"; continue; }
  if awk -F'= *' '
      /Inserted 1000 keys/ { ins = 1 }
      /^Total ops/ { t = $2 } /^member ops/ { m = $2 } /^insert ops/ { i = $2 } /^delete ops/ { d = $2 }
      END { exit !(ins && t == 100000 && m + i + d == t && m > i && m > d) }' <<<"$out"; then
    ok "$prog counts every operation"
  else bad "$prog counts"; echo "$out"; fi
done

build/pth_mat_vect_rand_split 4 400 400 >/dev/null && ok "pth_mat_vect_rand_split runs" || bad "pth_mat_vect_rand_split"
exit $fail
