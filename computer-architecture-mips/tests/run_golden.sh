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
  timeout 10 "$SPIM" -quiet -file "$src" < "$in" > /tmp/mips-raw.$$ 2>&1
  rc=$?
  # SPIM 8 prints its banner and "Loaded: .../exceptions.s" even with -quiet
  if head -1 /tmp/mips-raw.$$ | grep -q '^SPIM Version'; then
    sed '1,/^Loaded: /d' /tmp/mips-raw.$$ > /tmp/mips-actual.$$
  else
    cp /tmp/mips-raw.$$ /tmp/mips-actual.$$
  fi
  if [ $rc -eq 0 ] && cmp -s /tmp/mips-actual.$$ "$base.out"; then
    echo "ok   $name"
  else
    echo "FAIL $name ($src, exit $rc)"
    echo "  got:      $(od -An -c /tmp/mips-actual.$$ | tr -s ' ' | head -c 300)"
    echo "  expected: $(od -An -c "$base.out" | tr -s ' ' | head -c 300)"
    fail=1
  fi
done
rm -f /tmp/mips-actual.$$ /tmp/mips-raw.$$
echo "$count golden test(s), $([ $fail = 0 ] && echo all passed || echo FAILURES)"
exit $fail
