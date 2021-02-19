#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Usage: $0 NUMBER" 1>&2
	exit 1
fi

number="$1"
limit="1125899906842624"
if (( number < limit )); then
	go run main.go "$number"
else
	factor "$number"
fi
