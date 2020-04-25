#!/bin/bash
count=0
for i in $1/*$2; do
	let count++
done
echo $count
