#!/bin/bash

find . -type f \( -name '*.cpp' -o -name 'test_*.in' -o -name 'test_*.out' -o -name 'tags' -o -name '*.sh' -o -name 'README*' -o -name 'Makefile' \) -print | while read -r filename; do
	head -1 "$filename" | grep -q $'\r' && sed -i 's/\x0D$//' "$filename"
done
exit 0
