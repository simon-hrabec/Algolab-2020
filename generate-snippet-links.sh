#!/bin/bash

# Finds all headlines from the code snippets readme
# For each headlines creates a link into the main readme

REPO_PATH="${1:-https://github.com/simon-hrabec/Algolab2020/tree/main/}"
SNIPPETS_README_PATH="${REPO_PATH}code%20snippets#"

echo "## Code snippets"
echo "One of the most annoying thing about ALGOLAB (after the hard thinking ^^) is to always copy paste the right definitions for boost graphs, CGAL LP or flow edge adder. For this reason I put together a small set of useful snippets that should cover all your basic needs. It shoud prevent you from always searching the lecture notes or code examples for the relevant lines or going to the CGAL docs for basic syntax. You should find it here at one place. Some of the snippets are in fact the code from lectures or code examples (modified to some extent), some are written from scratch. The all attributions are listed in the code snippet descriptions."

grep '^##' code\ snippets/README.md | sed -E 's|.*\[(.*)\].*|\1|' | while read -r snippet; do\
	echo "- [${snippet}](${SNIPPETS_README_PATH}$(echo "${snippet}" | sed 's| |-|g'))"
done
