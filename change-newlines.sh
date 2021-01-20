#!/bin/bash

find . -type f \( -name '*.cpp' -o -name 'test_*.in' -o -name 'test_*.out' -o -name 'tags' -o -name '*.sh' -o -name 'README*' -o -name 'Makefile' \) -exec sed -i 's/\x0D$//' {} +
