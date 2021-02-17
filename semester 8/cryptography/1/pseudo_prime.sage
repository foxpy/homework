#!/usr/bin/env sage
from sage.misc.prandom import randrange

KEY_SIZE_MIN = 32
KEY_SIZE_MAX = 48

def random_prime():
	while True:
		t = randrange(KEY_SIZE_MAX - KEY_SIZE_MIN)
		s = KEY_SIZE_MIN + randrange(KEY_SIZE_MAX - KEY_SIZE_MIN - t)
		N = (2^s * t) - 1
		is_prime = False
		for i in range(int(s*log(t, 2))):
			a = 1 + randrange(N - 1)
			if N % a == 0:
				is_prime = False
				break
			elif (a*t) % N == 1:
				is_prime = False
				break
			elif not 0 <= log(-1 % N, a)/(2*t) < s:
				is_prime = False
				break
			else:
				is_prime = True
		if is_prime:
			return N

p = random_prime()
print(p)
