#!/usr/bin/env sage
import sys
import subprocess
p = 12491554796616397392007291845361681019980789084728846304013646795466302633346425772369277064638881858428879662416202925770315709968465491470753112581700067
q = 69008397991237478218529528711753578857464356221556536838757636132646301588781
a = 8305821956779628193852750508811757244889982632821843521491035713173371468528798753831744267407230704527461062321732669034432746173786958142572929772413468

def print_help(status):
	print(f"Usage: {sys.argv[0]} COMMAND ...")
	print(f"Where COMMAND is one of these:")
	print(f"\tgen PRIV PUB")
	print(f"\tsign PRIV MESSAGE DIGEST")
	print(f"\tverify PUB MESSAGE DIGEST")
	exit(status)

def hash(path):
	p = subprocess.Popen("gostsum %s | awk '{print $1}'" % path, stdout=subprocess.PIPE, shell = True)
	out, _ = p.communicate()
	return int("0x" + out.strip().hex(), 16)

def gen(priv, pub):
	x = randint(2, q)
	y = pow(a, x, p)
	with open(priv, "w") as f:
		f.write(str(x))
	with open(pub, "w") as f:
		f.write(str(y))

def sign(priv, msg, dgst):
	with open(priv, "r") as f:
		x = int(f.read(4096))
	r = 0
	while r == 0:
		k = randint(2, q)
		r = int(pow(a, k, p)) % q
		h = hash(msg) % q
		if h == 0: h = 1
		s = (x*r + k*h) % q
	with open(dgst, "w") as f:
		f.write(str(r) + "\n" + str(s))

def verify(pub, msg, dgst):
	v = pow(hash(msg), q - 2, q)
	with open(dgst, "r") as f:
		l = f.readlines()
		r = int(l[0])
		s = int(l[1])
	z1 = (s*v) % q
	z2 = ((q - r)*v) % q
	with open(pub, "r") as f:
		y = Integer(int(f.read(4096)))
	u = ((int(pow(a, z1, p)) * int(pow(y, z2, p))) % p) % q
	if (r == u):
		print("Document is signed correctly")
	else:
		print("Document sign invalid")

if len(sys.argv) < 2:
	print_help(0)
elif sys.argv[1] == "gen":
	if len(sys.argv) != 4:
		print_help(1)
	else:
		gen(sys.argv[2], sys.argv[3])
		exit()
elif sys.argv[1] == "sign":
	if len(sys.argv) != 5:
		print_help(1)
	else:
		sign(sys.argv[2], sys.argv[3], sys.argv[4])
		exit()
elif sys.argv[1] == "verify":
	if len(sys.argv) != 5:
		print_help(1)
	else:
		verify(sys.argv[2], sys.argv[3], sys.argv[4])
		exit()
else:
	print_help(1)
