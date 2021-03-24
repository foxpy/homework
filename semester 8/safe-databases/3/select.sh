#!/bin/bash

for i in $(seq 30); do
	/usr/bin/time -o time.txt -f "%e" -a psql -d istudents -c "SELECT count(id) FROM istudents.mark WHERE tmark_fk = $i" >/dev/null
done

let "i = 1"
echo "N, Time"
while read l; do
	echo "$i, $l"
	let "i = i + 1"
done < time.txt

rm time.txt
