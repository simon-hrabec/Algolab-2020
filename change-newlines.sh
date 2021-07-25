#!/bin/bash

# Locates all relevant text files (i.e. not PDFs but source codes, readmes, test cases and scripts)
# Checks by the first line if there are windows (\r\n) or linux (\n) line endings
# Converts all windows line endings for those files to linux ones

find . -type f \( -name '*.cpp' -o -name 'tags' -o -name '*.sh' -o -name 'README*' -o -name 'Makefile' \) -print | while read -r filename; do
	head -1 "$filename" | grep -q $'\r' && sed -i 's|\x0D$||' "$filename"
done
exit 0
