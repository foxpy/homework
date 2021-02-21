#!/usr/bin/env sage
import sys
from sage.misc.prandom import randrange
q = 30
if len(sys.argv) != 2:
	print(f"Usage: {sys.argv[0]} MESSAGE")
	sys.exit(1)
input = []
for i in sys.argv[1]:
	input.append(ord(i))
print(f"Input string: {sys.argv[1]}")
print(f"Input: {input}")

p = random_prime(2^q-1, 2^(q-1))
g = GF(p).multiplicative_generator()
x = randrange(1, p)
y = pow(g, x, p)
print(f"Public key: ({p}, {g}, {y})")
print(f"Private key: {x}")

ciphertext = []
for M in input:
	k = randrange(1, p)
	a = pow(g, k, p)
	b = (pow(y, k, p) * M) % p
	ciphertext.append((a, b))
print(f"Session key: {k}")
print(f"Ciphertext: {ciphertext}")

plaintext = []
decoded = ""
for (a, b) in ciphertext:
	M = (pow(a, p-1-x, p) * b) % p
	plaintext.append(M)
	decoded += chr(M)
print(f"Plaintext: {plaintext}")
print(f"Output: {decoded}")
