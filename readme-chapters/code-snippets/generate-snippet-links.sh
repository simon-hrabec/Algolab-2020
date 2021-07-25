#!/bin/bash

# Finds all headlines from the code snippets readme
# For each headlines creates a link into the main readme

REPO_PATH="${1:-https://github.com/simon-hrabec/Algolab2020/tree/main/}"
SNIPPETS_README_PATH="${REPO_PATH}code-snippets#"
SNIPPETS_README=$(git rev-parse --show-toplevel)"/code-snippets/README.md"

grep '^##' ${SNIPPETS_README} | sed -E 's|.*\[(.*)\].*|\1|' | while read -r snippet; do\
	echo "- [${snippet}](${SNIPPETS_README_PATH}$(echo "${snippet}" | sed 's| |-|g'))"
done
