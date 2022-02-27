#!/bin/bash

set -euo pipefail
IFS=$'\n\t'

encoding_print() {
	printf '>>> %s >>>\n' "$1"
	grep -P '[а-яА-ЯёЁ]' <<< "$2" >/dev/null && echo "$2" || echo "invalid"
	echo
}

main() {
	path="$1"
	raw="$(cargo run --bin steg --release --quiet -- "$path")"
	koi8r="$(iconv -f KOI8R -t UTF-8 <(printf '%s' "$raw") -o -)"
	cp866="$(iconv -f CP866 -t UTF-8 <(printf '%s' "$raw") -o -)"
	win1251="$(iconv -f WINDOWS-1251 -t UTF-8 <(printf '%s' "$raw") -o -)"
	bodo="$(cargo run --bin bodo --release --quiet -- --path=<(printf '%s' "$raw"))"
	encoding_print "KOI8R" "$koi8r"
	encoding_print "CP866" "$cp866"
	encoding_print "Windows-1251" "$win1251"
	encoding_print "МТК-2" "$bodo"
}

if [ "$#" != 1 ]; then
	printf "Usage: $0 input.docx\n" >&2
	exit 0
fi

main "$@"
