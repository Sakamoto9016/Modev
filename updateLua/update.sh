#!/usr/bin/env bash

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TARGET_DIR="$SCRIPT_DIR/.."

for file in "$SCRIPT_DIR"/*; do
    # Skip directories and the script itself
    [[ -f "$file" ]] || continue
    [[ "$file" == "$0" ]] && continue

    name="$(basename "$file")"

    if [[ -f "$TARGET_DIR/$name" ]]; then
        echo "Replacing $name"
        mv -f "$file" "$TARGET_DIR/$name"
    else
        echo "Keeping $name (not found in ../)"
    fi
done