#!/bin/bash

for ((i=0; i<3000;i+=100)); do
	/usr/bin/time -o time.txt -f "%e" -a psql --csv -d istudents -c \
		"SELECT mark.id FROM istudents.mark INNER JOIN istudents.studplan ON mark.studplan_fk = studplan.id LIMIT 100 OFFSET $i;" >/dev/null
done

let "i = 1"
echo "N, Time"
while read l; do
	echo "$i, $l"
	let "i = i + 1"
done < time.txt
rm time.txt
