#!/bin/bash

for i in $(seq 30); do
	/usr/bin/time -o time.txt -f "%e" -a psql -A -d istudents -c \
		"INSERT INTO istudents.mark(tmark_fk, studplan_fk, value, mdate, attendance, plyear) VALUES($i, 250, 12, current_timestamp, 120, 14);" >/dev/null
done

let "i = 1"
echo "N, Time"
while read l; do
	echo "$i, $l"
	let "i = i + 1"
done < time.txt

rm time.txt
