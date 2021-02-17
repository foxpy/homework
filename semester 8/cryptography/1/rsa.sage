#!/usr/bin/env sage

import sys
if len(sys.argv) != 2:
	print(f"Usage: {sys.argv[0]} INPUT")

p = random_prime(20000, 5000)
q = random_prime(20000, 5000)
n = p*q
m = (p - 1) * (q - 1)
e = random_prime(m, 100)
R = Integers(m)
d = R(1) / R(e)

print(f"p = {p}")
print(f"q = {q}")
print(f"n = {n}")
print(f"m = {m}")
print(f"d = {d}")
print(f"e = {e}")

input = sys.argv[1]
encrypted = []
decrypted = []
for i in input:
	message = ord(i)
	enc = pow(message, e, n)
	dec = pow(enc, d, n)
	encrypted.append(enc)
	decrypted.append(dec)
output = ""
for i in decrypted:
	output += chr(i)

print(f"Input: {input}")
print(f"Encrypted: {encrypted}")
print(f"Decrypted: {decrypted}")
print(f"Output: {output}")
