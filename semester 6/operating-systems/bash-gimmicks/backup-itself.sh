#!/bin/bash
mkdir -p "$HOME/backup"
source="$BASH_SOURCE"
destination="$HOME/backup/$(basename "$BASH_SOURCE").tar"
tar -c "$source" > "$destination"
