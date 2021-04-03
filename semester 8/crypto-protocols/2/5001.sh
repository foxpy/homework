#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

cp "5000.sh" "tmp.sh"
sed -i "s/5000/5001/g" "tmp.sh"
./tmp.sh
rm "tmp.sh"
