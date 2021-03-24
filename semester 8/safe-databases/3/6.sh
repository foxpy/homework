#!/bin/bash

main() {
	years="$(psql --csv -d istudents -c "SELECT DISTINCT plyear FROM istudents.mark WHERE plyear IS NOT NULL;" | tail +2)"
	echo "$years" | while read i; do
		printf "%s: " "$i"
		psql --csv -d istudents -c "SELECT count(id) FROM istudents.mark WHERE value > 40 AND plyear = $i" | tail +2
	done
}

export -f main
time="$(/usr/bin/time -f "%e" bash -c "main" 3>&1 1>&2 2>&3)"
echo "time: $time"
