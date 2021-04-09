#!/usr/bin/env sage
from sage.misc.prandom import randrange
K=32
p = random_prime(2^96, 2^48)
q = random_prime(2^96, 2^48)
n = p*q
print(f"n={n}")
V = []
S = []
for i in range(K):
	x = randrange(2, n)
	R = Integers(n)
	Vi = R(x)*R(x)
	Si = sqrt(R(1) / R(Vi))
	V.append(Vi)
	S.append(Si)
print(f"V={V}")
print(f"S={S}")

x = []
b = []
responce = []
status = []
for i in range(K):
	r = randrange(2, n)
	xi = (r^2) % n
	x.append(xi)
	bi = randrange(0, 2)
	b.append(bi)
	if (bi == 0):
		responce.append(r)
		if xi == (r^2) % n:
			status.append("OK")
		else:
			status.append("ALERT")
	else:
		y = (r*S[i]) % n
		responce.append(y)
		if xi == ((y^2)*V[i]) % n:
			status.append("OK")
		else:
			status.append("ALERT")

ret = True
for i in status:
	if i == 'OK':
		ret &= True
	else:
		ret &= False

print(f"x: {x}")
print(f"b: {b}")
print(f"responce: {responce}")
print(f"status: {status}")
print(f"Authenticated: {ret}")
