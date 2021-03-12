#!/usr/bin/env python3
import sys

def gcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, x, y = gcd(b%a, a)
        return (g, y-(b//a)*x, x)

def inv(b, n):
    g, x, _ = gcd(b, n)
    if g == 1:
        return x%n
    else:
        return None

if len(sys.argv) != 3:
    print(f"Usage: {sys.argv[0]} A P")
else:
    a, p = int(sys.argv[1]), int(sys.argv[2])
    i = inv(a, p)
    if i != None:
        print(i)
    else:
        print(f"Usage: {sys.argv[0]} A P")
