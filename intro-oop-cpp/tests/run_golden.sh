#!/usr/bin/env bash
# Golden tests: for every tests/golden/<program>.<case>.in, run build/<program>
# with that file on stdin and compare stdout with <program>.<case>.out.
set -u
cd "$(dirname "$0")/.."
fail=0; count=0
for in in tests/golden/*.in; do
  base=${in%.in}
  prog=$(basename "$base"); prog=${prog%%.*}
  expected=$base.out
  actual=$(timeout 20 "build/$prog" < "$in" 2>&1)
  count=$((count + 1))
  if [ "$actual" == "$(cat "$expected")" ]; then
    echo "ok   $(basename "$base")"
  else
    echo "FAIL $(basename "$base")"
    diff <(echo "$actual") "$expected" | head -20
    fail=1
  fi
done
echo "$count golden test(s), $([ $fail = 0 ] && echo all passed || echo FAILURES)"
exit $fail
