#!/bin/bash
while test -f "$1"; do
	echo "Waiting $2 seconds on semaphore"
	sleep $2
done
echo > "$1"
echo "Locked semaphore for $3 seconds"
sleep $3
rm "$1"
