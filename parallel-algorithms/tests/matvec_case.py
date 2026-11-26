"""Writes the stdin for mulmatrizvector (A is 100x100, x has 100 entries) or,
with --expected, the Y line it must print. Integer entries keep y exact."""
import sys

N = M = 100
A = [[(3 * i + 7 * j) % 11 - 5 for j in range(N)] for i in range(M)]
x = [(j % 7) - 3 for j in range(N)]

if "--expected" in sys.argv:
    y = [sum(A[i][j] * x[j] for j in range(N)) for i in range(M)]
    print("".join("%f " % v for v in y))
else:
    print(" ".join(str(v) for row in A for v in row))
    print(" ".join(str(v) for v in x))
