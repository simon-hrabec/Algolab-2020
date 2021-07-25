#!/bin/bash

# Seaches all problems and their 'tag' file
# Creates a list and adds each problem to all relevant categories
# Generates README list of those with links

REPO_PATH="${1:-https://github.com/simon-hrabec/Algolab2020/tree/main/problems/}"
PROBLEMS_DIR=$(git rev-parse --show-toplevel)"/problems/"

cd ${PROBLEMS_DIR}

find . -type f -name "tags" -exec cat {} \; | sort | uniq | while read -r tag; do
	echo -n "- ${tag} -"
	grep -rl "$tag" */tags | while read -r problem; do
		echo -n " [W$(echo "$problem" | sed 's/[^0-9]*//g' )/$(echo "$problem" | sed 's|.* - \(.*\)/tags|\1|g')]"
		echo -n "($REPO_PATH$(echo "$problem" | sed 's|/tags||g' | sed 's| |%20|g'))"
	done
	printf "\n"
done
