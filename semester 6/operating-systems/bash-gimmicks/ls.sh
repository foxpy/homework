#!/bin/bash
for i in $1/*; do
	stat "$i" | grep Access | head -1
	echo -e "\t$(basename "$i")"
done
