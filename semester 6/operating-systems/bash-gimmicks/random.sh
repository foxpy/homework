#!/bin/bash
for i in $(seq 25); do
	for i in $(seq 64); do
		rnd="BEGIN{printf \"%c\", $(( 97 + $RANDOM % 26 ))}"
		awk "$rnd"
	done
	echo
done
