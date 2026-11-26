#!/usr/bin/env bash
# Golden tests: tests/golden/<program>.<case>.in is fed to `spim` running
# <program>.asm ("Practica-pal" means Practica/pal.asm) and its stdout must
# equal <program>.<case>.out byte for byte.
set -u
cd "$(dirname "$0")/.."
SPIM=${SPIM:-spim}
fail=0; count=0
for in in tests/golden/*.in; do
  base=${in%.in}
  name=$(basename "$base"); prog=${name%%.*}; src=${prog//-//}.asm
  count=$((count + 1))
  if timeout 10 "$SPIM" -quiet -file "$src" < "$in" > /tmp/mips-actual.$$ 2>&1 &&
     cmp -s /tmp/mips-actual.$$ "$base.out"; then
    echo "ok   $name"
  else
    echo "FAIL $name ($src)"
    diff <(od -c /tmp/mips-actual.$$) <(od -c "$base.out") | head -20
    fail=1
  fi
done
rm -f /tmp/mips-actual.$$
echo "$count golden test(s), $([ $fail = 0 ] && echo all passed || echo FAILURES)"
exit $fail
