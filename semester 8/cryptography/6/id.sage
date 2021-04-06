#!/usr/bin/env sage
from sage.misc.prandom import randrange
p = random_prime(2^96, 2^48)
q = random_prime(2^96, 2^48)
n = p*q
x = randrange(2, n)
R = Integers(n)
V = R(x)*R(x)
S = sqrt(R(1) / R(V))
print(f"n: {n}\nS (public): {S}\nV (private): {V}")

for i in range(32):
	r = randrange(2, n)
	x = (r^2) % n
	print(f"A -> x: {x} -> B")
	b = randrange(0, 2)
	print(f"B -> b: {b} -> A")
	if (b == 0):
		print(f"A -> r: {r} -> B")
		if x == (r^2) % n:
			print("B: OK")
		else:
			print("B: ALERT")
			exit()
	else:
		y = (r*S) % n
		print(f"A -> y: {y} -> B")
		if x == ((y^2)*V) % n:
			print("B: OK")
		else:
			print("B: ALERT")
			exit()
print("A has been identified to B successfully")
