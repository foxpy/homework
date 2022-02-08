#!/bin/bash

set -euo pipefail
IFS=$'\n\t'

encoding_print() {
	printf '%s: ' "$1"
	grep -P '[а-яА-ЯёЁ]' <<< "$2" >/dev/null && echo "$2" || echo "invalid"
}

main() {
	path="$1"
	raw="$(cargo run --release --quiet -- "$path")"
	koi8r="$(iconv -f KOI8R -t UTF-8 <(printf '%s' "$raw") -o -)"
	cp866="$(iconv -f CP866 -t UTF-8 <(printf '%s' "$raw") -o -)"
	win1251="$(iconv -f WINDOWS-1251 -t UTF-8 <(printf '%s' "$raw") -o -)"
	encoding_print "KOI8R" "$koi8r"
	encoding_print "CP866" "$cp866"
	encoding_print "Windows-1251" "$win1251"
}

if [ "$#" != 1 ]; then
	printf "Usage: $0 input.docx\n" >&2
	exit 0
fi

main "$@"
