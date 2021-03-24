#!/bin/bash

main() {
	psql --csv -d istudents -c "SELECT plyear, count(id) FROM istudents.mark WHERE plyear IS NOT NULL AND value > 40 GROUP BY plyear;" | tail +2
}

export -f main
time="$(/usr/bin/time -f "%e" bash -c "main" 3>&1 1>&2 2>&3)"
echo "time: $time"
