#!/usr/bin/env sage
import sys
import hashlib

def print_help(status):
	print(f"Usage: {sys.argv[0]} COMMAND ...")
	print(f"Where COMMAND is one of these:")
	print(f"\tgen PUB PRIV")
	print(f"\tsign PUB PRIV INPUT OUTPUT")
	print(f"\tverify PUB MESSAGE DIGEST")
	exit(status)

def hash(path):
	sha1 = hashlib.sha1()
	with open(path, "rb") as f:
		while True:
			d = f.read(4096)
			if not d:
				break
			sha1.update(d)
	return int("0x" + sha1.hexdigest(), 16)

def gen(pub, priv):
	p = random_prime(2^512, 2^500)
	q = random_prime(2^512, 2^500)
	n = p*q
	m = (p-1)*(q-1)
	e = 65537 # IETF exponent
	R = Integers(m)
	d = R(1) / R(e)
	with open(pub, "w") as f:
		f.write(str(n))
	with open(priv, "w") as f:
		f.write(str(d))

def sign(pub, priv, in_file, out_file):
	with open(pub, "r") as f:
		n = int(f.read(4096))
	with open(priv, "r") as f:
		d = int(f.read(4096))
	m = hash(in_file)
	c = pow(m, d, n)
	with open(out_file, "w") as f:
		f.write(str(c))

def verify(pub, msg, dig):
	with open(pub, "r") as f:
		n = int(f.read(4096))
	m = hash(msg)
	with open(dig, "r") as f:
		c = int(f.read(4096))
	e = 65537 # IETF exponent
	d = pow(c, e, n)
	if m == d:
		print("Document is signed correctly")
	else:
		print("Document sign is incorrect")

if len(sys.argv) < 2:
	print_help(0)
elif sys.argv[1] == "gen":
	if len(sys.argv) != 4:
		print_help(1)
	else:
		gen(sys.argv[2], sys.argv[3])
		exit()
elif sys.argv[1] == "sign":
	if len(sys.argv) != 6:
		print_help(1)
	else:
		sign(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])
		exit()
elif sys.argv[1] == "verify":
	if len(sys.argv) != 5:
		print_help(1)
	else:
		verify(sys.argv[2], sys.argv[3], sys.argv[4])
		exit()
else:
	print_help(1)
