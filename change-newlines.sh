#!/bin/bash

find . -type f \( -name '*.cpp' -o -name 'tags' -o -name '*.sh' -o -name 'README*' -o -name 'Makefile' \) -exec sed -i 's/\x0D$//' {} +
