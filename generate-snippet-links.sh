#!/bin/bash

REPO_PATH="${1:-https://github.com/simon-hrabec/Algolab2020/tree/main/}"
SNIPPETS_README_PATH='${REPO_PATH}code%20snippets#'

echo "## Code snippets"
echo "One of the most annoying thing about ALGOLAB (after thinking hard ^^) is to always copy paste the right definitions for boost graphs, CGAL LP or flow edge adder. For this reason I put together a small set of useful snippets that should cover all your basic needs. No more reading throu lectures to find the code, searching through all the code examples again or copy pasting from old problems. Here everything is at one place."

grep '^##' code\ snippets/README.md | sed -E 's|.*\[(.*)\].*|\1|' | while read -r snippet; do\
	echo "- [${snippet}](${SNIPPETS_README_PATH}$(echo "${snippet}" | sed 's| |-|g'))"
done
