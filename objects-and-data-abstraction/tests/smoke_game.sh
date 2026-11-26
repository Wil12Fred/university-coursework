#!/usr/bin/env bash
# Headless run of the ncurses game in a pseudo-terminal. With no key presses
# the snake zig-zags down to the tank, so the game must end by itself and
# print "Game Over".
set -u
cd "$(dirname "$0")/.."
out=$(TERM=xterm timeout 60 script -qec 'echo "6 3" | build/game' /dev/null)
rc=$?
if [ $rc -eq 0 ] && grep -q "Game Over" <<<"$out"; then
  echo "ok   game ends with Game Over"
else
  echo "FAIL game (exit $rc)"; exit 1
fi
# The puzzle prints the solved board first, then a shuffle of the same tiles.
out=$(build/puzzle </dev/null)
expected=$'1 2 3 4 \n5 6 7 8 \n9 A B C \nD E F   '
if [ "$(head -4 <<<"$out")" == "$expected" ]; then
  echo "ok   puzzle starts from the solved board"
else
  echo "FAIL puzzle"; echo "$out" | head -4; exit 1
fi
